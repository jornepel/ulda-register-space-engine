/* ulda.h — ULDA Topological Decoder Engine */
#ifndef ULDA_H
#define ULDA_H

#include <stdint.h>
#include <stddef.h>

typedef uint64_t u64;
typedef int64_t  i64;

/* The coordinate: macros, vingers, kootjes */
typedef struct {
    i64 macros;
    i64 vingers;
    i64 kootjes;
} coordinaat;

/* Lifecycle */
void carry(coordinaat *c);
coordinaat bereken(u64 eenheid);
u64 coordinaat_naar_eenheid(coordinaat c);

/* Operations */
coordinaat add(coordinaat a, coordinaat b);
int sub(coordinaat a, coordinaat b, coordinaat *out);
coordinaat mul(coordinaat a, u64 n);
int div_op(coordinaat a, u64 n, coordinaat *out);

/* Write */
void write_coordinaat(const coordinaat *c, char *buf, size_t size);

#endif
