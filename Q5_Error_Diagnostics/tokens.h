#ifndef TOKENS_H
#define TOKENS_H

#include "golem.tab.h"

static inline const char* token2string(int token) {
    switch(token) {
        case GRID: return "GRID";
        case OBSTACLE: return "OBSTACLE";
        case BLUEPRINT: return "BLUEPRINT";
        case CONSTRUCT: return "CONSTRUCT";
        case SPAWN: return "SPAWN";
        case AT: return "AT";
        case AS: return "AS";
        case GO: return "GO";
        case TURN: return "TURN";
        case SCAN: return "SCAN";
        case PICK: return "PICK";
        case DROP: return "DROP";
        case IF: return "IF";
        case REPEAT: return "REPEAT";
        case NORTH: return "NORTH";
        case SOUTH: return "SOUTH";
        case EAST: return "EAST";
        case WEST: return "WEST";
        case TRUE: return "TRUE";
        case FALSE: return "FALSE";
        case EMPTY: return "EMPTY";
        case IDENTIFIER: return "IDENTIFIER";
        case INTEGER: return "INTEGER";
        case STRING_LITERAL: return "STRING_LITERAL";
        case EAST_SCAN: return "EAST_SCAN";
        case WEST_SCAN: return "WEST_SCAN";
        case NORTH_SCAN: return "NORTH_SCAN";
        case SOUTH_SCAN: return "SOUTH_SCAN";
        case EQ_OP: return "EQ_OP";
        case NE_OP: return "NE_OP";
        case PLUS: return "PLUS";
        case MINUS: return "MINUS";
        case MULTIPLY: return "MULTIPLY";
        case DIVIDE: return "DIVIDE";
        case ';': return "SEMICOLON";
        case '{': return "LBRACE";
        case '}': return "RBRACE";
        case ',': return "COMMA";
        case '(': return "LPAREN";
        case ')': return "RPAREN";
        case '?': return "QUERY";
        // [FLAG: Add keyword] Add token to string mapping here as needed
        default: return "UNKNOWN";
    }
}

#endif
