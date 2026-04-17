%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ir.h"
#include "helpers.h"

void yyerror(const char *s);
int yylex(void);
extern int yylineno;
static char *lookup_blueprint_label(const char *name);
static void register_blueprint_label(const char *name, const char *label);
static char *ensure_construct_entry_label(void);
static char *ensure_program_end_label(void);
static char *ensure_spawn_x_slot(void);
static char *ensure_spawn_y_slot(void);
static char *ensure_spawn_id_slot(void);
static char *emit_direction_check(const char *direction, const char *scan_result, int invert_result);
static void free_blueprint_labels(void);
static int entry_jump_emitted = 0;

typedef struct BlueprintLabel {
	char *name;
	char *label;
	struct BlueprintLabel *next;
} BlueprintLabel;

static BlueprintLabel *blueprint_labels = NULL;
static char *construct_entry_label = NULL;
static char *program_end_label = NULL;
static char *spawn_x_slot = NULL;
static char *spawn_y_slot = NULL;
static char *spawn_id_slot = NULL;
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
%type <sval> blueprint_header
%type <ctrl> if_prefix repeat_prefix

/* Operator precedence and associativity - FIXED FOR CONFLICTS */
%left PLUS MINUS
%left MULTIPLY DIVIDE MODULO
%right UMINUS

/* Precedence rule to resolve dangling else - CONFLICT RESOLUTION */
%nonassoc THEN
%nonassoc ELSE

%%

translation_unit:
	program
	{
		emit_quad("label", NULL, NULL, ensure_program_end_label());
		free_blueprint_labels();
		entry_jump_emitted = 0;
	}
	;

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
	GRID '(' expr ',' expr ')'
	{
		if (!$3.is_const || !$5.is_const) {
			yyerror("Grid dimensions must be constant integer expressions");
			YYERROR;
		}
		if ($3.val < 0 || $5.val < 0) {
			yyerror("Grid dimensions must be non-negative");
			YYERROR;
		}
		emit_quad("create_canvas", $3.place, $5.place, NULL);
	}
	'{' obstacle_list '}'
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
		emit_quad("load_obstacle", $3.place, $5.place, NULL);
	}
	;

blueprint_decl:
	blueprint_header '{' stmt_list '}'
	{
		emit_quad("goto", NULL, NULL, ensure_program_end_label());
		free($1);
	}
	;

blueprint_header:
	BLUEPRINT IDENTIFIER
	{
		if (!entry_jump_emitted) {
			emit_quad("goto", NULL, NULL, ensure_construct_entry_label());
			entry_jump_emitted = 1;
		}

		char *bp_label = new_label();
		register_blueprint_label($2, bp_label);
		emit_quad("label", NULL, NULL, bp_label);
		emit_quad("load_golem", ensure_spawn_x_slot(), ensure_spawn_y_slot(), ensure_spawn_id_slot());
		$$ = bp_label;
	}
	;

construct_decl:
	CONSTRUCT
	{
		emit_quad("label", NULL, NULL, ensure_construct_entry_label());
	}
	'{' spawn_list '}'
	{
		emit_quad("goto", NULL, NULL, ensure_program_end_label());
	}
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

		char *bp_label = lookup_blueprint_label($2);
		if (!bp_label) {
			yyerror("Spawn references undefined blueprint");
			YYERROR;
		}

		emit_quad("=", $5.place, NULL, ensure_spawn_x_slot());
		emit_quad("=", $7.place, NULL, ensure_spawn_y_slot());
		emit_quad("goto", NULL, NULL, bp_label);
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

		char *bp_label = lookup_blueprint_label($2);
		if (!bp_label) {
			yyerror("Spawn references undefined blueprint");
			YYERROR;
		}

		emit_quad("=", $7.place, NULL, ensure_spawn_x_slot());
		emit_quad("=", $9.place, NULL, ensure_spawn_y_slot());
		emit_quad("goto", NULL, NULL, bp_label);
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
	{}
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
		emit_quad("if_eq", ctrl.counter_place, "0", ctrl.end_label);
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
		emit_quad("go", ensure_spawn_id_slot(), $2.place, NULL);
	}
	;

rotation_stmt:
	TURN direction ';'
	{
		const char *angle = "0";
		if (strcmp($2, "north") == 0) {
			angle = "0";
		} else if (strcmp($2, "east") == 0) {
			angle = "90";
		} else if (strcmp($2, "south") == 0) {
			angle = "180";
		} else if (strcmp($2, "west") == 0) {
			angle = "270";
		}
		emit_quad("rot_golem", ensure_spawn_id_slot(), angle, NULL);
		free($2);
	}
	;

pick_stmt:
	PICK IDENTIFIER ';'
	{}
	;

drop_stmt:
	DROP IDENTIFIER ';'
	{}
	;

conditional_stmt:
	if_prefix stmt %prec THEN
	{
		emit_quad("label", NULL, NULL, $1.false_label);
		emit_quad("label", NULL, NULL, $1.end_label);
		free($1.false_label);
		free($1.end_label);
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
	}
	| repeat_inf_prefix compound_stmt
	{
		emit_quad("goto", NULL, NULL, $1);
		free($1);
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
		char *temp = emit_direction_check($1, $3, 0);
		free($1);
		free($3);
		$$ = temp;
	}
	| directional_scan NE_OP scan_result
	{
		char *temp = emit_direction_check($1, $3, 1);
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
	fprintf(stderr, "Parse error at line %d: %s\n", yylineno, s);
}

static char *lookup_blueprint_label(const char *name) {
	BlueprintLabel *node = blueprint_labels;
	while (node) {
		if (strcmp(node->name, name) == 0) {
			return node->label;
		}
		node = node->next;
	}
	return NULL;
}

static void register_blueprint_label(const char *name, const char *label) {
	BlueprintLabel *node = (BlueprintLabel *)malloc(sizeof(BlueprintLabel));
	node->name = strdup(name);
	node->label = strdup(label);
	node->next = blueprint_labels;
	blueprint_labels = node;
}

static char *ensure_construct_entry_label(void) {
	if (!construct_entry_label) {
		construct_entry_label = new_label();
	}
	return construct_entry_label;
}

static char *ensure_program_end_label(void) {
	if (!program_end_label) {
		program_end_label = new_label();
	}
	return program_end_label;
}

static char *ensure_spawn_x_slot(void) {
	if (!spawn_x_slot) {
		spawn_x_slot = new_temp();
	}
	return spawn_x_slot;
}

static char *ensure_spawn_y_slot(void) {
	if (!spawn_y_slot) {
		spawn_y_slot = new_temp();
	}
	return spawn_y_slot;
}

static char *ensure_spawn_id_slot(void) {
	if (!spawn_id_slot) {
		spawn_id_slot = new_temp();
	}
	return spawn_id_slot;
}

static void free_blueprint_labels(void) {
	BlueprintLabel *node = blueprint_labels;
	while (node) {
		BlueprintLabel *next = node->next;
		free(node->name);
		free(node->label);
		free(node);
		node = next;
	}
	blueprint_labels = NULL;

	if (construct_entry_label) {
		free(construct_entry_label);
		construct_entry_label = NULL;
	}

	if (program_end_label) {
		free(program_end_label);
		program_end_label = NULL;
	}

	if (spawn_x_slot) {
		free(spawn_x_slot);
		spawn_x_slot = NULL;
	}

	if (spawn_y_slot) {
		free(spawn_y_slot);
		spawn_y_slot = NULL;
	}

	if (spawn_id_slot) {
		free(spawn_id_slot);
		spawn_id_slot = NULL;
	}
}

static char *emit_direction_check(const char *direction, const char *scan_result, int invert_result) {
	char *base_x = ensure_spawn_x_slot();
	char *base_y = ensure_spawn_y_slot();
	char *target_x = strdup(base_x);
	char *target_y = strdup(base_y);
	char *offset = int_to_string(1);

	if (strcmp(direction, ">>") == 0) {
		char *tmp = new_temp();
		emit_quad("+", base_x, offset, tmp);
		free(target_x);
		target_x = tmp;
	} else if (strcmp(direction, "<<") == 0) {
		char *tmp = new_temp();
		emit_quad("-", base_x, offset, tmp);
		free(target_x);
		target_x = tmp;
	} else if (strcmp(direction, "^^") == 0) {
		char *tmp = new_temp();
		emit_quad("-", base_y, offset, tmp);
		free(target_y);
		target_y = tmp;
	} else if (strcmp(direction, "vv") == 0) {
		char *tmp = new_temp();
		emit_quad("+", base_y, offset, tmp);
		free(target_y);
		target_y = tmp;
	}

	char *check_temp = new_temp();
	emit_quad("check_empty", target_x, target_y, check_temp);

	char *result_temp = check_temp;
	int scan_is_empty = strcmp(scan_result, "empty") == 0;
	if ((scan_is_empty && invert_result) || (!scan_is_empty && !invert_result)) {
		char *inverted_temp = new_temp();
		emit_quad("not", check_temp, NULL, inverted_temp);
		result_temp = inverted_temp;
	}

	free(target_x);
	free(target_y);
	free(offset);
	return result_temp;
}
