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
}

/* Semantic value type */
%union {
	int ival;
	char *sval;
	ExprAttr expr;
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

/* FIXED: Added %prec THEN to resolve dangling else */
conditional_stmt:
	IF '(' condition ')' stmt %prec THEN
	{
		printf("    if (...) stmt\n");
	}
	| IF '(' condition ')' stmt ELSE stmt
	{
		printf("    if (...) stmt else stmt\n");
	}
	;

/* FIXED: Separated productions to avoid R/R conflict */
repetition_stmt:
	REPEAT expr compound_stmt
	{
		if (!$2.is_const) {
			yyerror("Repeat count must be a constant integer expression");
			YYERROR;
		}
		if ($2.val < 0) {
			yyerror("Repeat count cannot be negative");
			YYERROR;
		}
		emit_quad("repeat", $2.place, NULL, NULL);
		printf("    repeat %d { ... }\n", $2.val);
	}
	| REPEAT compound_stmt
	{
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
	| SCAN '(' direction '?' ')' NE_OP scan_result
	| directional_scan EQ_OP scan_result
	| directional_scan NE_OP scan_result
	;

directional_scan:
	EAST_SCAN
	| WEST_SCAN
	| NORTH_SCAN
	| SOUTH_SCAN
	;

scan_result:
	OBSTACLE
	| EMPTY
	;

direction:
	NORTH
	| SOUTH
	| EAST
	| WEST
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
