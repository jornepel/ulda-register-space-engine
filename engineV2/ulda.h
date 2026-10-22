/* ulda.h — ULDA Topological Decoder Engine */
#ifndef ULDA_H
#define ULDA_H

#include <stdint.h>
#include <stddef.h>

typedef uint64_t u64;
typedef int64_t  i64;

/* The coordinate: seven scales of the true Sumerian ladder */
typedef struct {
    i64 sar_gal_shu_nu_tag_ga;  /* 12,960,000 */
    i64 sar_gal;                /* 216,000 */
    i64 saru;                   /* 36,000 */
    i64 sar;                    /* 3,600 */
    i64 full_macro;             /* 360 */
    i64 u;                      /* 36 */
    i64 dis;                    /* 6 (the true 1-cycle) */
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
