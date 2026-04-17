#ifndef IR_H
#define IR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ====== IR (Intermediate Representation) Infrastructure ====== */

/* Quadruple structure for Three Address Code */
typedef struct Quadruple {
	char *op;
	char *arg1;
	char *arg2;
	char *result;
} Quadruple;

/* Linked list to store all emitted quadruples */
typedef struct QuadNode {
	Quadruple quad;
	struct QuadNode *next;
} QuadNode;

char *new_temp(void);
char *new_label(void);
void emit_quad(const char *op, const char *arg1, const char *arg2, const char *result);
void print_ir(void);
void free_ir(void);

#endif
