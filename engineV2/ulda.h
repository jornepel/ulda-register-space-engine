/* ulda.h — ULDA Topological Decoder Engine */
#ifndef ULDA_H
#define ULDA_H

#include <stdint.h>
#include <stddef.h>

typedef uint64_t u64;
typedef int64_t  i64;

/* The coordinate: macros, fingers, knuckles */
typedef struct {
    i64 macros;
    i64 fingers;
    i64 knuckles;
} coordinate;

/* Lifecycle */
void carry(coordinate *c);
coordinate calculate(u64 unit);
u64 coordinate_to_unit(coordinate c);

/* Operations */
coordinate add(coordinate a, coordinate b);
int subtract(coordinate a, coordinate b, coordinate *out);
coordinate multiply(coordinate a, u64 n);
int divide(coordinate a, u64 n, coordinate *out);

/* Write */
void write_coordinate(const coordinate *c, char *buf, size_t size);

#endif
