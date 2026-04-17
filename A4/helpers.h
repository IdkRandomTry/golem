#ifndef HELPERS_H
#define HELPERS_H

#include <stdio.h>
#include <stdlib.h>

static inline char *int_to_string(int value) {
    char *buf = (char *)malloc(32);
    sprintf(buf, "%d", value);
    return buf;
}

#endif
