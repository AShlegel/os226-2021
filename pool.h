#pragma once

#include "util.h"

#define POOL_INITIALIZER(_mem, _nmemb, _membsz) { \
    .mem = (char*)(_mem), \
    .membsz    = (_membsz), \
    .freehead = NULL, \
    .freestart = (char*)(_mem), \
    .freeend = (char*)(_mem) + (_nmemb) * (_membsz), \
}

#define POOL_INITIALIZER_ARRAY(_array) \
    POOL_INITIALIZER(_array, ARRAY_SIZE(_array), sizeof((_array)[0]));

struct pool_free_block {
    struct pool_free_block *next;
};

struct pool {
    char *mem;
    unsigned long membsz;
    char *freestart;
    char *freeend;
    struct pool_free_block *freehead;
};

void pool_init(struct pool *p, void *mem, unsigned long nmemb, unsigned long membsz);

void *pool_alloc(struct pool *p);

void pool_free(struct pool *p, void *ptr);
