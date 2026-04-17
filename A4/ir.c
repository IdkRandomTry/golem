#include "ir.h"

static QuadNode *ir_head = NULL;
static QuadNode *ir_tail = NULL;
static int quad_count = 0;
static int temp_count = 0;
static int label_count = 0;

char *new_temp(void) {
    char *temp = (char *)malloc(16);
    sprintf(temp, "t%d", ++temp_count);
    return temp;
}

char *new_label(void) {
    char *label = (char *)malloc(16);
    sprintf(label, "L%d", ++label_count);
    return label;
}

void emit_quad(const char *op, const char *arg1, const char *arg2, const char *result) {
    QuadNode *node = (QuadNode *)malloc(sizeof(QuadNode));
    node->quad.op = (char *)malloc(strlen(op) + 1);
    strcpy(node->quad.op, op);

    node->quad.arg1 = arg1 ? (char *)malloc(strlen(arg1) + 1) : NULL;
    if (arg1) strcpy(node->quad.arg1, arg1);

    node->quad.arg2 = arg2 ? (char *)malloc(strlen(arg2) + 1) : NULL;
    if (arg2) strcpy(node->quad.arg2, arg2);

    node->quad.result = result ? (char *)malloc(strlen(result) + 1) : NULL;
    if (result) strcpy(node->quad.result, result);

    node->next = NULL;

    if (ir_head == NULL) {
        ir_head = node;
    } else {
        ir_tail->next = node;
    }
    ir_tail = node;
    quad_count++;
}

void print_ir(void) {
    QuadNode *node;
    int idx = 1;

    if (quad_count == 0) {
        return;
    }

    printf("\nGenerated Intermediate Code (3AC Quadruples):\n");
    printf("#    | op              | arg1       | arg2       | result\n");
    printf("-----|-----------------|------------|------------|------------\n");

    node = ir_head;
    while (node) {
        printf("%-4d | %-15s | %-10s | %-10s | %-10s\n",
               idx,
               node->quad.op,
               node->quad.arg1 ? node->quad.arg1 : "-",
               node->quad.arg2 ? node->quad.arg2 : "-",
               node->quad.result ? node->quad.result : "-");
        node = node->next;
        idx++;
    }
    printf("\n");
}

void free_ir(void) {
    QuadNode *node = ir_head;
    while (node) {
        QuadNode *next = node->next;
        free(node->quad.op);
        if (node->quad.arg1) free(node->quad.arg1);
        if (node->quad.arg2) free(node->quad.arg2);
        if (node->quad.result) free(node->quad.result);
        free(node);
        node = next;
    }

    ir_head = NULL;
    ir_tail = NULL;
    quad_count = 0;
    temp_count = 0;
    label_count = 0;
}
