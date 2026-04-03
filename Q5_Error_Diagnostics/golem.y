%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void yyerror(const char *s);
int yylex(void);

extern int yylineno;
extern char *yytext;
extern FILE *yyin;

/* Error tracking */
int error_count = 0;
int warning_count = 0;

/* Input buffer for context display */
#define MAX_LINE_LENGTH 1024
char current_line[MAX_LINE_LENGTH];
int current_line_number = 0;

/* Enhanced error reporting */
void syntax_error(const char *msg, const char *token) {
    error_count++;
    fprintf(stderr, "\n");
    fprintf(stderr, "╔════════════════════════════════════════════════════════════════╗\n");
    fprintf(stderr, "║                      SYNTAX ERROR #%-3d                        ║\n", error_count);
    fprintf(stderr, "╚════════════════════════════════════════════════════════════════╝\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "Location: Line %d\n", yylineno);
    fprintf(stderr, "Error:    %s\n", msg);
    if (token && strlen(token) > 0) {
        fprintf(stderr, "Token:    '%s'\n", token);
    }
    fprintf(stderr, "\n");
    
    /* Provide helpful suggestions */
    fprintf(stderr, "Possible causes:\n");
    if (strstr(msg, "syntax error") || strstr(msg, "unexpected")) {
        fprintf(stderr, "  • Missing semicolon (;) at the end of statement\n");
        fprintf(stderr, "  • Unmatched parentheses () or braces {}\n");
        fprintf(stderr, "  • Invalid token or keyword\n");
        fprintf(stderr, "  • Missing required keyword or operator\n");
    }
    fprintf(stderr, "\n");
}

void semantic_error(const char *msg) {
    error_count++;
    fprintf(stderr, "\n");
    fprintf(stderr, "╔════════════════════════════════════════════════════════════════╗\n");
    fprintf(stderr, "║                     SEMANTIC ERROR #%-3d                       ║\n", error_count);
    fprintf(stderr, "╚════════════════════════════════════════════════════════════════╝\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "Location: Line %d\n", yylineno);
    fprintf(stderr, "Error:    %s\n", msg);
    fprintf(stderr, "\n");
}

void warning_message(const char *msg) {
    warning_count++;
    fprintf(stderr, "\n");
    fprintf(stderr, "⚠ Warning #%d (Line %d): %s\n", warning_count, yylineno, msg);
    fprintf(stderr, "\n");
}

%}

/* Semantic value type */
%union {
	int ival;
	char *sval;
}

/* Enable better error messages */
%define parse.error verbose
%locations

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
%type <ival> expr

/* Operator precedence and associativity */
%left PLUS MINUS
%left MULTIPLY DIVIDE MODULO
%right UMINUS

/* Precedence rule to resolve dangling else */
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
	| error ';'
	{
		syntax_error("Invalid statement", yytext);
		fprintf(stderr, "Recovery: Skipping to next semicolon\n\n");
		yyerrok;
	}
	;

grid_decl:
	GRID '(' expr ',' expr ')' '{' obstacle_list '}'
	{
		if ($3 < 0 || $5 < 0) {
			semantic_error("Grid dimensions must be non-negative");
			fprintf(stderr, "Found: grid(%d, %d)\n", $3, $5);
			fprintf(stderr, "Expected: Both dimensions >= 0\n\n");
			YYERROR;
		}
		if ($3 == 0 || $5 == 0) {
			warning_message("Grid has zero dimension");
		}
		printf("  Grid: %d x %d\n", $3, $5);
	}
	| GRID error '}'
	{
		syntax_error("Invalid grid declaration", NULL);
		fprintf(stderr, "Expected: grid(rows, cols) { ... }\n\n");
		yyerrok;
	}
	;

obstacle_list:
	| obstacle_list obstacle_stmt
	| obstacle_list error
	{
		syntax_error("Invalid obstacle statement", NULL);
		fprintf(stderr, "Expected: obstacle(x, y);\n\n");
		yyerrok;
	}
	;

obstacle_stmt:
	OBSTACLE '(' expr ',' expr ')' ';'
	{
		if ($3 < 0 || $5 < 0) {
			semantic_error("Obstacle coordinates must be non-negative");
			fprintf(stderr, "Found: obstacle(%d, %d)\n", $3, $5);
			fprintf(stderr, "Expected: Both coordinates >= 0\n\n");
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
	| BLUEPRINT error '}'
	{
		syntax_error("Invalid blueprint declaration", NULL);
		fprintf(stderr, "Expected: blueprint name { ... }\n\n");
		yyerrok;
	}
	;

construct_decl:
	CONSTRUCT '{' spawn_list '}'
	| CONSTRUCT error '}'
	{
		syntax_error("Invalid construct declaration", NULL);
		fprintf(stderr, "Expected: construct { spawn statements }\n\n");
		yyerrok;
	}
	;

spawn_list:
	| spawn_list spawn_stmt
	| spawn_list error
	{
		syntax_error("Invalid spawn statement in construct block", NULL);
		yyerrok;
	}
	;

spawn_stmt:
	SPAWN IDENTIFIER AT '(' expr ',' expr ')' ';'
	{
		if ($5 < 0 || $7 < 0) {
			semantic_error("Spawn coordinates must be non-negative");
			fprintf(stderr, "Found: spawn %s at (%d, %d)\n", $2, $5, $7);
			fprintf(stderr, "Expected: Both coordinates >= 0\n\n");
			YYERROR;
		}
		printf("  Spawn '%s' at (%d, %d)\n", $2, $5, $7);
	}
	| SPAWN IDENTIFIER AS IDENTIFIER AT '(' expr ',' expr ')' ';'
	{
		if ($7 < 0 || $9 < 0) {
			semantic_error("Spawn coordinates must be non-negative");
			fprintf(stderr, "Found: spawn %s as %s at (%d, %d)\n", $2, $4, $7, $9);
			fprintf(stderr, "Expected: Both coordinates >= 0\n\n");
			YYERROR;
		}
		printf("  Spawn '%s' (alias '%s') at (%d, %d)\n", $2, $4, $7, $9);
	}
	| SPAWN error ';'
	{
		syntax_error("Invalid spawn statement", NULL);
		fprintf(stderr, "Expected: spawn name at (x, y);\n");
		fprintf(stderr, "      or: spawn name as alias at (x, y);\n\n");
		yyerrok;
	}
	;

stmt_list:
	| stmt_list stmt
	| stmt_list error
	{
		syntax_error("Invalid statement in statement list", NULL);
		yyerrok;
	}
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

compound_stmt:
	'{' stmt_list '}'
	{
		printf("    { compound statements }\n");
	}
	| '{' error '}'
	{
		syntax_error("Invalid compound statement", NULL);
		yyerrok;
	}
	;

movement_stmt:
	GO expr ';'
	{
		if ($2 == 0) {
			warning_message("Movement with 0 steps has no effect");
			printf("    go 0;  (no movement)\n");
		} else if ($2 < 0) {
			int steps = -$2;
			printf("    go -%d;  (turn 180°, move %d steps forward, face reversed direction)\n", steps, steps);
		} else {
			printf("    go %d;  (move %d steps forward)\n", $2, $2);
		}
	}
	| GO error ';'
	{
		syntax_error("Invalid movement statement", NULL);
		fprintf(stderr, "Expected: go <number>;\n\n");
		yyerrok;
	}
	;

rotation_stmt:
	TURN direction ';'
	{
		printf("    turn direction;\n");
	}
	| TURN error ';'
	{
		syntax_error("Invalid turn statement", NULL);
		fprintf(stderr, "Expected: turn <direction>;\n");
		fprintf(stderr, "Directions: north, south, east, west\n\n");
		yyerrok;
	}
	;

pick_stmt:
	PICK IDENTIFIER ';'
	{
		printf("    pick %s;\n", $2);
	}
	| PICK error ';'
	{
		syntax_error("Invalid pick statement", NULL);
		fprintf(stderr, "Expected: pick <identifier>;\n\n");
		yyerrok;
	}
	;

drop_stmt:
	DROP IDENTIFIER ';'
	{
		printf("    drop %s;\n", $2);
	}
	| DROP error ';'
	{
		syntax_error("Invalid drop statement", NULL);
		fprintf(stderr, "Expected: drop <identifier>;\n\n");
		yyerrok;
	}
	;

conditional_stmt:
	IF '(' condition ')' stmt %prec THEN
	{
		printf("    if (...) stmt\n");
	}
	| IF '(' condition ')' stmt ELSE stmt
	{
		printf("    if (...) stmt else stmt\n");
	}
	| IF error stmt
	{
		syntax_error("Invalid if statement", NULL);
		fprintf(stderr, "Expected: if (condition) statement\n");
		fprintf(stderr, "      or: if (condition) statement else statement\n\n");
		yyerrok;
	}
	;

repetition_stmt:
	REPEAT expr compound_stmt
	{
		if ($2 < 0) {
			semantic_error("Repeat count cannot be negative");
			fprintf(stderr, "Found: repeat %d { ... }\n", $2);
			fprintf(stderr, "Expected: count >= 0\n\n");
			YYERROR;
		}
		if ($2 == 0) {
			warning_message("Repeat with 0 iterations has no effect");
		}
		printf("    repeat %d { ... }\n", $2);
	}
	| REPEAT compound_stmt
	{
		printf("    repeat (infinite) { ... }\n");
	}
	| REPEAT expr ';'
	{
		if ($2 < 0) {
			semantic_error("Repeat count cannot be negative");
			fprintf(stderr, "Found: repeat %d;\n", $2);
			fprintf(stderr, "Expected: count >= 0\n\n");
			YYERROR;
		}
		printf("    repeat %d; (single iteration marker)\n", $2);
	}
	| REPEAT error
	{
		syntax_error("Invalid repeat statement", NULL);
		fprintf(stderr, "Expected: repeat { ... }\n");
		fprintf(stderr, "      or: repeat <count> { ... }\n\n");
		yyerrok;
	}
	;

condition:
	SCAN '(' direction '?' ')' EQ_OP scan_result
	| SCAN '(' direction '?' ')' NE_OP scan_result
	| directional_scan EQ_OP scan_result
	| directional_scan NE_OP scan_result
	| error
	{
		syntax_error("Invalid condition", NULL);
		fprintf(stderr, "Expected: scan(direction?) == result\n");
		fprintf(stderr, "      or: directional_scan == result\n\n");
		yyerrok;
	}
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
	| MINUS expr %prec UMINUS
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
			semantic_error("Division by zero");
			fprintf(stderr, "Expression: %d / %d\n", $1, $3);
			fprintf(stderr, "Division by zero is undefined\n\n");
			YYERROR;
		}
		$$ = $1 / $3;
	}
	| expr MODULO expr
	{
		if ($3 == 0) {
			semantic_error("Modulo by zero");
			fprintf(stderr, "Expression: %d %% %d\n", $1, $3);
			fprintf(stderr, "Modulo by zero is undefined\n\n");
			YYERROR;
		}
		$$ = $1 % $3;
	}
	| '(' expr ')'
	{
		$$ = $2;
	}
	| '(' error ')'
	{
		syntax_error("Invalid expression", NULL);
		fprintf(stderr, "Check for proper arithmetic expression syntax\n\n");
		$$ = 0;
		yyerrok;
	}
	;

%%

void yyerror(const char *s) {
	if (strstr(s, "syntax error") != NULL) {
		syntax_error(s, yytext);
	} else {
		fprintf(stderr, "\n╔════════════════════════════════════════════════════════════════╗\n");
		fprintf(stderr, "║                         PARSE ERROR                            ║\n");
		fprintf(stderr, "╚════════════════════════════════════════════════════════════════╝\n");
		fprintf(stderr, "\nLine %d: %s\n", yylineno, s);
		if (yytext && strlen(yytext) > 0) {
			fprintf(stderr, "Near token: '%s'\n", yytext);
		}
		fprintf(stderr, "\n");
	}
}
