%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ir.h"
#include "helpers.h"

void yyerror(const char *s);
int yylex(void);
%}

%code requires {
	typedef struct ExprAttr {
		int val;
		int is_const;
		char *place;
	} ExprAttr;

	typedef struct ControlAttr {
		char *start_label;
		char *false_label;
		char *end_label;
		char *counter_place;
	} ControlAttr;
}

/* Semantic value type */
%union {
	int ival;
	char *sval;
	ExprAttr expr;
	ControlAttr ctrl;
}

/* Token declarations */
%token GRID OBSTACLE BLUEPRINT CONSTRUCT SPAWN AT AS
%token GO TURN SCAN PICK DROP
%token IF ELSE REPEAT THEN
%token NORTH SOUTH EAST WEST
%token TRUE FALSE EMPTY
%token EAST_SCAN WEST_SCAN NORTH_SCAN SOUTH_SCAN
%token EQ_OP NE_OP
%token PLUS MINUS MULTIPLY DIVIDE MODULO

%token <ival> INTEGER
%token <sval> IDENTIFIER STRING_LITERAL

/* Rule types */
%type <expr> expr
%type <sval> condition directional_scan scan_result direction repeat_inf_prefix
%type <ctrl> if_prefix repeat_prefix

/* Operator precedence and associativity - FIXED FOR CONFLICTS */
%left PLUS MINUS
%left MULTIPLY DIVIDE MODULO
%right UMINUS

/* Precedence rule to resolve dangling else - CONFLICT RESOLUTION */
%nonassoc THEN
%nonassoc ELSE

%%

program:
	| program statement
	;

statement:
	grid_decl
	| blueprint_decl
	| construct_decl
	| ';'
	;

grid_decl:
	GRID '(' expr ',' expr ')' '{' obstacle_list '}'
	{
		if (!$3.is_const || !$5.is_const) {
			yyerror("Grid dimensions must be constant integer expressions");
			YYERROR;
		}
		if ($3.val < 0 || $5.val < 0) {
			yyerror("Grid dimensions must be non-negative");
			YYERROR;
		}
		printf("  Grid: %d x %d\n", $3.val, $5.val);
	}
	;

obstacle_list:
	| obstacle_list obstacle_stmt
	;

obstacle_stmt:
	OBSTACLE '(' expr ',' expr ')' ';'
	{
		if (!$3.is_const || !$5.is_const) {
			yyerror("Obstacle coordinates must be constant integer expressions");
			YYERROR;
		}
		if ($3.val < 0 || $5.val < 0) {
			yyerror("Obstacle coordinates must be non-negative");
			YYERROR;
		}
		printf("  Obstacle at (%d, %d)\n", $3.val, $5.val);
	}
	;

blueprint_decl:
	BLUEPRINT IDENTIFIER '{' stmt_list '}'
	{
		printf("Blueprint '%s' defined\n", $2);
	}
	;

construct_decl:
	CONSTRUCT '{' spawn_list '}'
	;

spawn_list:
	| spawn_list spawn_stmt
	;

spawn_stmt:
	SPAWN IDENTIFIER AT '(' expr ',' expr ')' ';'
	{
		if (!$5.is_const || !$7.is_const) {
			yyerror("Spawn coordinates must be constant integer expressions");
			YYERROR;
		}
		if ($5.val < 0 || $7.val < 0) {
			yyerror("Spawn coordinates must be non-negative");
			YYERROR;
		}
		printf("  Spawn '%s' at (%d, %d)\n", $2, $5.val, $7.val);
	}
	| SPAWN IDENTIFIER AS IDENTIFIER AT '(' expr ',' expr ')' ';'
	{
		if (!$7.is_const || !$9.is_const) {
			yyerror("Spawn coordinates must be constant integer expressions");
			YYERROR;
		}
		if ($7.val < 0 || $9.val < 0) {
			yyerror("Spawn coordinates must be non-negative");
			YYERROR;
		}
		printf("  Spawn '%s' (alias '%s') at (%d, %d)\n", $2, $4, $7.val, $9.val);
	}
	;

stmt_list:
	| stmt_list stmt
	;

stmt:
	movement_stmt
	| rotation_stmt
	| pick_stmt
	| drop_stmt
	| conditional_stmt
	| repetition_stmt
	| compound_stmt
	;

/* FIXED: compound_stmt instead of stmt_block to avoid R/R conflict */
compound_stmt:
	'{' stmt_list '}'
	{
		printf("    { compound statements }\n");
	}
	;

if_prefix:
	IF '(' condition ')'
	{
		ControlAttr ctrl;
		ctrl.start_label = NULL;
		ctrl.false_label = new_label();
		ctrl.end_label = new_label();
		ctrl.counter_place = NULL;
		emit_quad("if_false_goto", $3, NULL, ctrl.false_label);
		free($3);
		$$ = ctrl;
	}
	;

repeat_prefix:
	REPEAT expr
	{
		if (!$2.is_const) {
			yyerror("Repeat count must be a constant integer expression");
			YYERROR;
		}
		if ($2.val < 0) {
			yyerror("Repeat count cannot be negative");
			YYERROR;
		}

		ControlAttr ctrl;
		ctrl.start_label = new_label();
		ctrl.false_label = NULL;
		ctrl.end_label = new_label();
		ctrl.counter_place = new_temp();

		char *count_text = int_to_string($2.val);
		emit_quad("=", count_text, NULL, ctrl.counter_place);
		emit_quad("label", NULL, NULL, ctrl.start_label);
		emit_quad("if_eq_zero", ctrl.counter_place, NULL, ctrl.end_label);
		free(count_text);

		$$ = ctrl;
	}
	;

repeat_inf_prefix:
	REPEAT
	{
		char *start_label = new_label();
		emit_quad("label", NULL, NULL, start_label);
		$$ = start_label;
	}
	;

movement_stmt:
	GO expr ';'
	{
		emit_quad("go", $2.place, NULL, NULL);
		if (!$2.is_const) {
			printf("    go %s;  (runtime expression)\n", $2.place);
		} else if ($2.val == 0) {
			printf("    go 0;  (no movement)\n");
		} else if ($2.val < 0) {
			int steps = -$2.val;
			printf("    go -%d;  (turn 180°, move %d steps forward, face reversed direction)\n", steps, steps);
		} else {
			printf("    go %d;  (move %d steps forward)\n", $2.val, $2.val);
		}
	}
	;

rotation_stmt:
	TURN direction ';'
	{
		printf("    turn direction;\n");
	}
	;

pick_stmt:
	PICK IDENTIFIER ';'
	{
		printf("    pick %s;\n", $2);
	}
	;

drop_stmt:
	DROP IDENTIFIER ';'
	{
		printf("    drop %s;\n", $2);
	}
	;

conditional_stmt:
	if_prefix stmt %prec THEN
	{
		emit_quad("label", NULL, NULL, $1.false_label);
		emit_quad("label", NULL, NULL, $1.end_label);
		free($1.false_label);
		free($1.end_label);
		printf("    if (...) stmt\n");
	}
	| if_prefix stmt ELSE
	{
		emit_quad("goto", NULL, NULL, $1.end_label);
		emit_quad("label", NULL, NULL, $1.false_label);
	} stmt
	{
		emit_quad("label", NULL, NULL, $1.end_label);
		free($1.false_label);
		free($1.end_label);
		printf("    if (...) stmt else stmt\n");
	}
	;

repetition_stmt:
	repeat_prefix compound_stmt
	{
		emit_quad("sub", $1.counter_place, "1", $1.counter_place);
		emit_quad("goto", NULL, NULL, $1.start_label);
		emit_quad("label", NULL, NULL, $1.end_label);
		free($1.start_label);
		free($1.end_label);
		free($1.counter_place);
		printf("    repeat { ... }\n");
	}
	| repeat_inf_prefix compound_stmt
	{
		emit_quad("goto", NULL, NULL, $1);
		free($1);
		printf("    repeat (infinite) { ... }\n");
	}
	| REPEAT expr ';'
	{
		if (!$2.is_const) {
			yyerror("Repeat count must be a constant integer expression");
			YYERROR;
		}
		if ($2.val < 0) {
			yyerror("Repeat count cannot be negative");
			YYERROR;
		}
		emit_quad("repeat_once", $2.place, NULL, NULL);
		printf("    repeat %d; (single iteration marker)\n", $2.val);
	}
	;

condition:
	SCAN '(' direction '?' ')' EQ_OP scan_result
	{
		char *temp = new_temp();
		emit_quad("cond_scan_eq", $3, $7, temp);
		free($3);
		free($7);
		$$ = temp;
	}
	| SCAN '(' direction '?' ')' NE_OP scan_result
	{
		char *temp = new_temp();
		emit_quad("cond_scan_ne", $3, $7, temp);
		free($3);
		free($7);
		$$ = temp;
	}
	| directional_scan EQ_OP scan_result
	{
		char *temp = new_temp();
		emit_quad("cond_dir_eq", $1, $3, temp);
		free($1);
		free($3);
		$$ = temp;
	}
	| directional_scan NE_OP scan_result
	{
		char *temp = new_temp();
		emit_quad("cond_dir_ne", $1, $3, temp);
		free($1);
		free($3);
		$$ = temp;
	}
	;

directional_scan:
	EAST_SCAN
	{
		$$ = strdup(">>");
	}
	| WEST_SCAN
	{
		$$ = strdup("<<");
	}
	| NORTH_SCAN
	{
		$$ = strdup("^^");
	}
	| SOUTH_SCAN
	{
		$$ = strdup("vv");
	}
	;

scan_result:
	OBSTACLE
	{
		$$ = strdup("obstacle");
	}
	| EMPTY
	{
		$$ = strdup("empty");
	}
	;

direction:
	NORTH
	{
		$$ = strdup("north");
	}
	| SOUTH
	{
		$$ = strdup("south");
	}
	| EAST
	{
		$$ = strdup("east");
	}
	| WEST
	{
		$$ = strdup("west");
	}
	;

expr:
	INTEGER
	{
		char *literal = int_to_string($1);
		char *temp = new_temp();
		emit_quad("=", literal, NULL, temp);
		$$.val = $1;
		$$.is_const = 1;
		$$.place = temp;
		free(literal);
	}
	| IDENTIFIER
	{
		$$.val = 0;
		$$.is_const = 0;
		$$.place = strdup($1);
	}
	| expr PLUS expr
	{
		char *temp = new_temp();
		emit_quad("+", $1.place, $3.place, temp);
		$$.is_const = $1.is_const && $3.is_const;
		$$.val = $$.is_const ? ($1.val + $3.val) : 0;
		$$.place = temp;
	}
	| expr MINUS expr
	{
		char *temp = new_temp();
		emit_quad("-", $1.place, $3.place, temp);
		$$.is_const = $1.is_const && $3.is_const;
		$$.val = $$.is_const ? ($1.val - $3.val) : 0;
		$$.place = temp;
	}
	| MINUS expr %prec UMINUS
	{
		char *temp = new_temp();
		emit_quad("uminus", $2.place, NULL, temp);
		$$.is_const = $2.is_const;
		$$.val = $2.is_const ? (-$2.val) : 0;
		$$.place = temp;
	}
	| expr MULTIPLY expr
	{
		char *temp = new_temp();
		emit_quad("*", $1.place, $3.place, temp);
		$$.is_const = $1.is_const && $3.is_const;
		$$.val = $$.is_const ? ($1.val * $3.val) : 0;
		$$.place = temp;
	}
	| expr DIVIDE expr
	{
		if ($3.is_const && $3.val == 0) {
			yyerror("Division by zero");
			YYERROR;
		}
		char *temp = new_temp();
		emit_quad("/", $1.place, $3.place, temp);
		$$.is_const = $1.is_const && $3.is_const;
		$$.val = $$.is_const ? ($1.val / $3.val) : 0;
		$$.place = temp;
	}
	| expr MODULO expr
	{
		if ($3.is_const && $3.val == 0) {
			yyerror("Modulo by zero");
			YYERROR;
		}
		char *temp = new_temp();
		emit_quad("%", $1.place, $3.place, temp);
		$$.is_const = $1.is_const && $3.is_const;
		$$.val = $$.is_const ? ($1.val % $3.val) : 0;
		$$.place = temp;
	}
	| '(' expr ')'
	{
		$$ = $2;
	}
	;

%%

void yyerror(const char *s) {
	fprintf(stderr, "Parse error: %s\n", s);
}
