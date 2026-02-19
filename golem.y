%{
#include <stdio.h>
#include <stdlib.h>

void yyerror(const char *s);
int yylex(void);
%}

/* Token declarations */
%token GRID OBSTACLE BLUEPRINT CONSTRUCT SPAWN AT AS
%token GO TURN SCAN PICK DROP
%token IF REPEAT
%token NORTH SOUTH EAST WEST
%token TRUE FALSE EMPTY
%token IDENTIFIER INTEGER STRING_LITERAL
%token EAST_SCAN WEST_SCAN NORTH_SCAN SOUTH_SCAN
%token EQ_OP NE_OP

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
	GRID '(' INTEGER ',' INTEGER ')' '{' obstacle_list '}'
	;

obstacle_list:
	| obstacle_list obstacle_stmt
	;

obstacle_stmt:
	OBSTACLE '(' INTEGER ',' INTEGER ')' ';'
	;

blueprint_decl:
	BLUEPRINT IDENTIFIER '{' stmt_list '}'
	;

construct_decl:
	CONSTRUCT '{' spawn_list '}'
	;

spawn_list:
	| spawn_list spawn_stmt
	;

spawn_stmt:
	SPAWN IDENTIFIER AT '(' INTEGER ',' INTEGER ')' ';'
	| SPAWN IDENTIFIER AS IDENTIFIER AT '(' INTEGER ',' INTEGER ')' ';'
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
	GO INTEGER ';'
	;

rotation_stmt:
	TURN direction ';'
	;

pick_stmt:
	PICK IDENTIFIER ';'
	;

drop_stmt:
	DROP IDENTIFIER ';'
	;

conditional_stmt:
	IF '(' condition ')' '{' stmt_list '}'
	;

repetition_stmt:
	REPEAT INTEGER '{' stmt_list '}'
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

%%

void yyerror(const char *s) {
	fprintf(stderr, "Parse error: %s\n", s);
}

int main(void) {
	printf("GOLEM Parser - Starting...\n");
	if (yyparse() == 0) {
		printf("Parse successful!\n");
	} else {
		printf("Parse failed.\n");
	}
	return 0;
}
