/* ulda.h — ULDA Topological Decoder Engine */
#ifndef ULDA_H
#define ULDA_H

#include <stdint.h>
#include <stddef.h>

typedef uint64_t u64;
typedef int64_t  i64;

/* 
 * The coordinate: Seven scales of the true Sumerian ladder.
 * Base units map linearly to the underlying radix hierarchy.
 * The carry thresholds are: x6 -> x10 -> x10 -> x10 -> x6 -> x60
 */
typedef struct {
    i64 sar_gal_shu_nu_tag_ga;  /* 12,960,000 units (60^5) */
    i64 sar_gal;                /*    216,000 units (60^3) */
    i64 saru;                   /*     36,000 units (10 * 60^2) */
    i64 sar;                    /*      3,600 units (60^2) */
    i64 full_macro;             /*        360 units (6 * 60 / the šár) */
    i64 u;                      /*         36 units (6^2) */
    i64 dis;                    /*          6 units (the operator step) */
} coordinate;

/* Lifecycle and Normalization Matrix */
void carry(coordinate *c);
coordinate calculate(u64 unit);
u64 coordinate_to_unit(coordinate c);

/* Arithmetic Operations */
coordinate add(coordinate a, coordinate b);
int subtract(coordinate a, coordinate b, coordinate *out);
coordinate multiply(coordinate a, u64 n);
int divide(coordinate a, u64 n, coordinate *out);

/* String Telemetry Serialization */
void write_coordinate(const coordinate *c, char *buf, size_t size);

#endif /* ULDA_H */
