/* ulda.h — ULDA Topological Decoder Engine */
#ifndef ULDA_H
#define ULDA_H

#include <stdint.h>
#include <stddef.h>

typedef uint64_t u64;

typedef struct {
    u64 *steps;
    u64 ranks;
    u64 capacity;
} ulda_register;

/* Lifecycle */
void reg_init(ulda_register *r, u64 capacity);
void reg_free(ulda_register *r);

/* The peel */
void peel(ulda_register *r, u64 n);

/* Reken: two coordinates, one operation */
int reken(ulda_register *out, u64 a, u64 b, char op);

/* Compass */
typedef struct { u64 x, y, z; } coord;
coord compass(u64 angle);

/* Write */
void write_register(const ulda_register *r, char *buf, size_t size);

#endif
