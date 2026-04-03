%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void yyerror(const char *s);
int yylex(void);

/* Derivation tree structure */
typedef struct DerivationNode {
    char *production;
    int rule_num;
    struct DerivationNode *next;
} DerivationNode;

DerivationNode *derivation_head = NULL;
DerivationNode *derivation_tail = NULL;
int derivation_count = 0;

/* Function to add a derivation step */
void add_derivation(const char *rule_desc, int rule_num) {
    DerivationNode *node = (DerivationNode*)malloc(sizeof(DerivationNode));
    node->production = strdup(rule_desc);
    node->rule_num = rule_num;
    node->next = NULL;
    
    if (derivation_tail == NULL) {
        derivation_head = derivation_tail = node;
    } else {
        derivation_tail->next = node;
        derivation_tail = node;
    }
    derivation_count++;
}

/* Function to display derivation tree in reverse order */
void display_reverse_derivation() {
    if (derivation_head == NULL) {
        printf("No derivations recorded.\n");
        return;
    }
    
    /* Store in array for reverse display */
    DerivationNode **arr = (DerivationNode**)malloc(derivation_count * sizeof(DerivationNode*));
    DerivationNode *current = derivation_head;
    int i = 0;
    
    while (current != NULL) {
        arr[i++] = current;
        current = current->next;
    }
    
    printf("\n╔════════════════════════════════════════════════════════════════╗\n");
    printf("║           REVERSE DERIVATION TREE (Bottom-Up)                 ║\n");
    printf("╠════════════════════════════════════════════════════════════════╣\n");
    printf("║ Total Derivation Steps: %-38d ║\n", derivation_count);
    printf("╚════════════════════════════════════════════════════════════════╝\n\n");
    
    /* Display in reverse order */
    for (i = derivation_count - 1; i >= 0; i--) {
        printf("[Step %3d/%d] Rule %2d: %s\n", 
               derivation_count - i, derivation_count, 
               arr[i]->rule_num, arr[i]->production);
    }
    
    printf("\n");
    free(arr);
}

/* Free derivation list */
void free_derivations() {
    DerivationNode *current = derivation_head;
    while (current != NULL) {
        DerivationNode *next = current->next;
        free(current->production);
        free(current);
        current = next;
    }
}

%}

/* Semantic value type */
%union {
	int ival;
	char *sval;
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
	{ add_derivation("program → ε", 1); }
	| program statement
	{ add_derivation("program → program statement", 2); }
	;

statement:
	grid_decl
	{ add_derivation("statement → grid_decl", 3); }
	| blueprint_decl
	{ add_derivation("statement → blueprint_decl", 4); }
	| construct_decl
	{ add_derivation("statement → construct_decl", 5); }
	| ';'
	{ add_derivation("statement → ';'", 6); }
	;

grid_decl:
	GRID '(' expr ',' expr ')' '{' obstacle_list '}'
	{
		add_derivation("grid_decl → GRID '(' expr ',' expr ')' '{' obstacle_list '}'", 7);
		if ($3 < 0 || $5 < 0) {
			yyerror("Grid dimensions must be non-negative");
			YYERROR;
		}
		printf("  Grid: %d x %d\n", $3, $5);
	}
	;

obstacle_list:
	{ add_derivation("obstacle_list → ε", 8); }
	| obstacle_list obstacle_stmt
	{ add_derivation("obstacle_list → obstacle_list obstacle_stmt", 9); }
	;

obstacle_stmt:
	OBSTACLE '(' expr ',' expr ')' ';'
	{
		add_derivation("obstacle_stmt → OBSTACLE '(' expr ',' expr ')' ';'", 10);
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
		add_derivation("blueprint_decl → BLUEPRINT IDENTIFIER '{' stmt_list '}'", 11);
		printf("Blueprint '%s' defined\n", $2);
	}
	;

construct_decl:
	CONSTRUCT '{' spawn_list '}'
	{ add_derivation("construct_decl → CONSTRUCT '{' spawn_list '}'", 12); }
	;

spawn_list:
	{ add_derivation("spawn_list → ε", 13); }
	| spawn_list spawn_stmt
	{ add_derivation("spawn_list → spawn_list spawn_stmt", 14); }
	;

spawn_stmt:
	SPAWN IDENTIFIER AT '(' expr ',' expr ')' ';'
	{
		add_derivation("spawn_stmt → SPAWN IDENTIFIER AT '(' expr ',' expr ')' ';'", 15);
		if ($5 < 0 || $7 < 0) {
			yyerror("Spawn coordinates must be non-negative");
			YYERROR;
		}
		printf("  Spawn '%s' at (%d, %d)\n", $2, $5, $7);
	}
	| SPAWN IDENTIFIER AS IDENTIFIER AT '(' expr ',' expr ')' ';'
	{
		add_derivation("spawn_stmt → SPAWN IDENTIFIER AS IDENTIFIER AT '(' expr ',' expr ')' ';'", 16);
		if ($7 < 0 || $9 < 0) {
			yyerror("Spawn coordinates must be non-negative");
			YYERROR;
		}
		printf("  Spawn '%s' (alias '%s') at (%d, %d)\n", $2, $4, $7, $9);
	}
	;

stmt_list:
	{ add_derivation("stmt_list → ε", 17); }
	| stmt_list stmt
	{ add_derivation("stmt_list → stmt_list stmt", 18); }
	;

stmt:
	movement_stmt
	{ add_derivation("stmt → movement_stmt", 19); }
	| rotation_stmt
	{ add_derivation("stmt → rotation_stmt", 20); }
	| pick_stmt
	{ add_derivation("stmt → pick_stmt", 21); }
	| drop_stmt
	{ add_derivation("stmt → drop_stmt", 22); }
	| conditional_stmt
	{ add_derivation("stmt → conditional_stmt", 23); }
	| repetition_stmt
	{ add_derivation("stmt → repetition_stmt", 24); }
	| compound_stmt
	{ add_derivation("stmt → compound_stmt", 25); }
	;

compound_stmt:
	'{' stmt_list '}'
	{
		add_derivation("compound_stmt → '{' stmt_list '}'", 26);
		printf("    { compound statements }\n");
	}
	;

movement_stmt:
	GO expr ';'
	{
		add_derivation("movement_stmt → GO expr ';'", 27);
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
		add_derivation("rotation_stmt → TURN direction ';'", 28);
		printf("    turn direction;\n");
	}
	;

pick_stmt:
	PICK IDENTIFIER ';'
	{
		add_derivation("pick_stmt → PICK IDENTIFIER ';'", 29);
		printf("    pick %s;\n", $2);
	}
	;

drop_stmt:
	DROP IDENTIFIER ';'
	{
		add_derivation("drop_stmt → DROP IDENTIFIER ';'", 30);
		printf("    drop %s;\n", $2);
	}
	;

conditional_stmt:
	IF '(' condition ')' stmt %prec THEN
	{
		add_derivation("conditional_stmt → IF '(' condition ')' stmt", 31);
		printf("    if (...) stmt\n");
	}
	| IF '(' condition ')' stmt ELSE stmt
	{
		add_derivation("conditional_stmt → IF '(' condition ')' stmt ELSE stmt", 32);
		printf("    if (...) stmt else stmt\n");
	}
	;

repetition_stmt:
	REPEAT expr compound_stmt
	{
		add_derivation("repetition_stmt → REPEAT expr compound_stmt", 33);
		if ($2 < 0) {
			yyerror("Repeat count cannot be negative");
			YYERROR;
		}
		printf("    repeat %d { ... }\n", $2);
	}
	| REPEAT compound_stmt
	{
		add_derivation("repetition_stmt → REPEAT compound_stmt", 34);
		printf("    repeat (infinite) { ... }\n");
	}
	| REPEAT expr ';'
	{
		add_derivation("repetition_stmt → REPEAT expr ';'", 35);
		if ($2 < 0) {
			yyerror("Repeat count cannot be negative");
			YYERROR;
		}
		printf("    repeat %d; (single iteration marker)\n", $2);
	}
	;

condition:
	SCAN '(' direction '?' ')' EQ_OP scan_result
	{ add_derivation("condition → SCAN '(' direction '?' ')' EQ_OP scan_result", 36); }
	| SCAN '(' direction '?' ')' NE_OP scan_result
	{ add_derivation("condition → SCAN '(' direction '?' ')' NE_OP scan_result", 37); }
	| directional_scan EQ_OP scan_result
	{ add_derivation("condition → directional_scan EQ_OP scan_result", 38); }
	| directional_scan NE_OP scan_result
	{ add_derivation("condition → directional_scan NE_OP scan_result", 39); }
	;

directional_scan:
	EAST_SCAN
	{ add_derivation("directional_scan → EAST_SCAN", 40); }
	| WEST_SCAN
	{ add_derivation("directional_scan → WEST_SCAN", 41); }
	| NORTH_SCAN
	{ add_derivation("directional_scan → NORTH_SCAN", 42); }
	| SOUTH_SCAN
	{ add_derivation("directional_scan → SOUTH_SCAN", 43); }
	;

scan_result:
	OBSTACLE
	{ add_derivation("scan_result → OBSTACLE", 44); }
	| EMPTY
	{ add_derivation("scan_result → EMPTY", 45); }
	;

direction:
	NORTH
	{ add_derivation("direction → NORTH", 46); }
	| SOUTH
	{ add_derivation("direction → SOUTH", 47); }
	| EAST
	{ add_derivation("direction → EAST", 48); }
	| WEST
	{ add_derivation("direction → WEST", 49); }
	;

expr:
	INTEGER
	{
		add_derivation("expr → INTEGER", 50);
		$$ = $1;
	}
	| expr PLUS expr
	{
		add_derivation("expr → expr PLUS expr", 51);
		$$ = $1 + $3;
	}
	| expr MINUS expr
	{
		add_derivation("expr → expr MINUS expr", 52);
		$$ = $1 - $3;
	}
	| MINUS expr %prec UMINUS
	{
		add_derivation("expr → MINUS expr", 53);
		$$ = -$2;
	}
	| expr MULTIPLY expr
	{
		add_derivation("expr → expr MULTIPLY expr", 54);
		$$ = $1 * $3;
	}
	| expr DIVIDE expr
	{
		add_derivation("expr → expr DIVIDE expr", 55);
		if ($3 == 0) {
			yyerror("Division by zero");
			YYERROR;
		}
		$$ = $1 / $3;
	}
	| expr MODULO expr
	{
		add_derivation("expr → expr MODULO expr", 56);
		if ($3 == 0) {
			yyerror("Modulo by zero");
			YYERROR;
		}
		$$ = $1 % $3;
	}
	| '(' expr ')'
	{
		add_derivation("expr → '(' expr ')'", 57);
		$$ = $2;
	}
	;

%%

void yyerror(const char *s) {
	fprintf(stderr, "Parse error: %s\n", s);
}
