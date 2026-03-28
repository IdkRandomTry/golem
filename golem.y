%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void yyerror(const char *s);
int yylex(void);
%}

/* Semantic value type */
%union {
	int ival;
	char *sval;
}

/* Token declarations */
%token GRID OBSTACLE BLUEPRINT CONSTRUCT SPAWN AT AS
%token GO TURN SCAN PICK DROP
%token IF REPEAT
%token NORTH SOUTH EAST WEST
%token TRUE FALSE EMPTY
%token EAST_SCAN WEST_SCAN NORTH_SCAN SOUTH_SCAN
%token EQ_OP NE_OP
%token PLUS MINUS MULTIPLY DIVIDE

%token <ival> INTEGER
%token <sval> IDENTIFIER STRING_LITERAL

/* Rule types */
%type <ival> expr

/* Operator precedence and associativity */
%left PLUS MINUS
%left MULTIPLY DIVIDE
%right UMINUS

%%
// [FLAG: Add keyword] declare token here

// Skeleton grammar - minimal rules 
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
		if ($3 < 0 || $5 < 0) {
			yyerror("Grid dimensions must be non-negative");
			YYERROR;
		}
		printf("  Grid: %d x %d\n", $3, $5);
	}
	;

obstacle_list:
	| obstacle_list obstacle_stmt
	;

obstacle_stmt:
	OBSTACLE '(' expr ',' expr ')' ';'
	{
		if ($3 < 0 || $5 < 0) {
			yyerror("Obstacle coordinates must be non-negative");
			YYERROR;
		}
		printf("  Obstacle at (%d, %d)\n", $3, $5);
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
		if ($5 < 0 || $7 < 0) {
			yyerror("Spawn coordinates must be non-negative");
			YYERROR;
		}
		printf("  Spawn '%s' at (%d, %d)\n", $2, $5, $7);
	}
	| SPAWN IDENTIFIER AS IDENTIFIER AT '(' expr ',' expr ')' ';'
	{
		if ($7 < 0 || $9 < 0) {
			yyerror("Spawn coordinates must be non-negative");
			YYERROR;
		}
		printf("  Spawn '%s' (alias '%s') at (%d, %d)\n", $2, $4, $7, $9);
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
	;

movement_stmt:
	GO expr ';'
	{
		if ($2 == 0) {
			printf("    go 0;  (no movement)\n");
		} else if ($2 < 0) {
			int steps = -$2;
			printf("    go -%d;  (turn 180°, move %d steps forward, face reversed direction)\n", steps, steps);
		} else {
			printf("    go %d;  (move %d steps forward)\n", $2, $2);
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
	IF '(' condition ')' '{' stmt_list '}'
	{
		printf("    if (...) { ... }\n");
	}
	;

repetition_stmt:
	REPEAT expr '{' stmt_list '}'
	{
		if ($2 < 0) {
			yyerror("Repeat count cannot be negative");
			YYERROR;
		}
		printf("    repeat %d { ... }\n", $2);
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
		$$ = $1;
	}
	| expr PLUS expr
	{
		$$ = $1 + $3;
	}
	| expr MINUS expr
	{
		$$ = $1 - $3;
	}
	| MINUS expr %prec MULTIPLY
	{
		$$ = -$2;
	}
	| expr MULTIPLY expr
	{
		$$ = $1 * $3;
	}
	| expr DIVIDE expr
	{
		if ($3 == 0) {
			yyerror("Division by zero");
			YYERROR;
		}
		$$ = $1 / $3;
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
