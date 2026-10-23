/* ulda.c — ULDA Topological Decoder Engine (cleaned) */
#include "ulda.h"
#include <stdio.h>
#include <limits.h>

/* ============================================================================
 * RADIX LADDER
 * ----------------------------------------------------------------------------
 * Column          Radix   Meaning
 * sar_gal_shu...  —       top (unbounded above)
 * sar_gal         60      macro group
 * saru            6       micro group
 * sar             10      decade
 * full_macro      10      decade
 * u               10      decade
 * dis             6       micro
 *
 * Borrow/carry propagate upward; each column knows the radix of the column
 * BELOW it (the one it lends to / borrows from).
 * ============================================================================
 */

#define RADIX_DIS        6
#define RADIX_U          10
#define RADIX_FULL_MACRO 10
#define RADIX_SAR        10
#define RADIX_SARU       6
#define RADIX_SAR_GAL    60

/* Borrow one from column above, add radix to column below. */
#define BORROW_UP(col_low, col_high, radix) \
    do { while ((col_low) < 0) { (col_low) += (radix); (col_high) -= 1; } } while (0)

/* Carry one to column above when column exceeds radix. */
#define CARRY_UP(col_low, col_high, radix) \
    do { while ((col_low) >= (radix)) { (col_low) -= (radix); (col_high) += 1; } } while (0)

/* ============================================================================
 * carry — normalize all columns in place.
 * Returns 0 if the top column went negative (underflow, cannot represent).
 * ============================================================================
 */
int carry(coordinate *c) {
    /* Step 1: borrow from top downward */
    BORROW_UP(c->dis,      c->u,          RADIX_DIS);
    BORROW_UP(c->u,        c->full_macro, RADIX_U);
    BORROW_UP(c->full_macro, c->sar,      RADIX_FULL_MACRO);
    BORROW_UP(c->sar,      c->saru,       RADIX_SAR);
    BORROW_UP(c->saru,     c->sar_gal,    RADIX_SARU);
    BORROW_UP(c->sar_gal,  c->sar_gal_shu_nu_tag_ga, RADIX_SAR_GAL);

    /* Step 2: carry from bottom upward */
    CARRY_UP(c->dis,        c->u,          RADIX_DIS);
    CARRY_UP(c->u,          c->full_macro, RADIX_U);
    CARRY_UP(c->full_macro, c->sar,        RADIX_FULL_MACRO);
    CARRY_UP(c->sar,        c->saru,       RADIX_SAR);
    CARRY_UP(c->saru,       c->sar_gal,    RADIX_SARU);
    CARRY_UP(c->sar_gal,    c->sar_gal_shu_nu_tag_ga, RADIX_SAR_GAL);

    /* Underflow check: top column must be non-negative. */
    return c->sar_gal_shu_nu_tag_ga >= 0;
}

/* ============================================================================
 * calculate — unit (u64) to coordinate.
 * ============================================================================
 */
coordinate calculate(u64 unit) {
    coordinate c = {0};

    c.sar_gal_shu_nu_tag_ga = (i64)(unit / 12960000ULL); unit %= 12960000ULL;
    c.sar_gal               = (i64)(unit / 216000ULL);   unit %= 216000ULL;
    c.saru                  = (i64)(unit / 36000ULL);    unit %= 36000ULL;
    c.sar                   = (i64)(unit / 3600ULL);     unit %= 3600ULL;
    c.full_macro            = (i64)(unit / 360ULL);      unit %= 360ULL;
    c.u                     = (i64)(unit / 36ULL);       unit %= 36ULL;
    c.dis                   = (i64)(unit / 6ULL);        unit %= 6ULL;

    /* The remainder (unit % 6) is dropped: the coordinate is in 6-unit steps.
     * If you need sub-dis precision, add a fractional column. */
    (void)carry(&c);
    return c;
}

/* ============================================================================
 * coordinate_to_unit — coordinate back to unit.
 * Returns 0 on overflow (out set to false).
 * ============================================================================
 */
int coordinate_to_unit(coordinate c, u64 *out) {
    u64 acc = 0;
    u64 term;

    /* Each term checked for overflow before adding. */
    #define ADD_TERM(col, scale) \
        do { \
            if ((u64)(col) > UINT64_MAX / (scale)) return 0; \
            term = (u64)(col) * (scale); \
            if (acc > UINT64_MAX - term) return 0; \
            acc += term; \
        } while (0)

    ADD_TERM(c.sar_gal_shu_nu_tag_ga, 12960000ULL);
    ADD_TERM(c.sar_gal,               216000ULL);
    ADD_TERM(c.saru,                  36000ULL);
    ADD_TERM(c.sar,                   3600ULL);
    ADD_TERM(c.full_macro,            360ULL);
    ADD_TERM(c.u,                     36ULL);
    ADD_TERM(c.dis,                   6ULL);

    #undef ADD_TERM

    *out = acc;
    return 1;
}

/* ============================================================================
 * add — coordinate + coordinate. Always succeeds (barring overflow of i64).
 * ============================================================================
 */
coordinate add(coordinate a, coordinate b) {
    coordinate c = {
        a.sar_gal_shu_nu_tag_ga + b.sar_gal_shu_nu_tag_ga,
        a.sar_gal               + b.sar_gal,
        a.saru                  + b.saru,
        a.sar                   + b.sar,
        a.full_macro            + b.full_macro,
        a.u                     + b.u,
        a.dis                   + b.dis
    };
    (void)carry(&c);
    return c;
}

/* ============================================================================
 * subtract — coordinate - coordinate.
 * Returns 0 on underflow (result would be negative).
 * ============================================================================
 */
int subtract(coordinate a, coordinate b, coordinate *out) {
    coordinate c = {
        a.sar_gal_shu_nu_tag_ga - b.sar_gal_shu_nu_tag_ga,
        a.sar_gal               - b.sar_gal,
        a.saru                  - b.saru,
        a.sar                   - b.sar,
        a.full_macro            - b.full_macro,
        a.u                     - b.u,
        a.dis                   - b.dis
    };
    if (!carry(&c)) return 0;
    *out = c;
    return 1;
}

/* ============================================================================
 * multiply — coordinate * scalar.
 * ============================================================================
 */
coordinate multiply(coordinate a, u64 n) {
    coordinate c = {
        a.sar_gal_shu_nu_tag_ga * (i64)n,
        a.sar_gal               * (i64)n,
        a.saru                  * (i64)n,
        a.sar                   * (i64)n,
        a.full_macro            * (i64)n,
        a.u                     * (i64)n,
        a.dis                   * (i64)n
    };
    (void)carry(&c);
    return c;
}

/* ============================================================================
 * divide — coordinate / scalar (integer division, via unit).
 * Returns 0 if n == 0 or if the coordinate does not fit in u64.
 * ============================================================================
 */
int divide(coordinate a, u64 n, coordinate *out) {
    u64 u;
    if (n == 0) return 0;
    if (!coordinate_to_unit(a, &u)) return 0;
    *out = calculate(u / n);
    return 1;
}

/* ============================================================================
 * write_coordinate — pretty print.
 * ============================================================================
 */
void write_coordinate(const coordinate *c, char *buf, size_t size) {
    snprintf(buf, size,
             "(%lld, %lld, %lld, %lld, %lld, %lld, %lld)",
             (long long)c->sar_gal_shu_nu_tag_ga,
             (long long)c->sar_gal,
             (long long)c->saru,
             (long long)c->sar,
             (long long)c->full_macro,
             (long long)c->u,
             (long long)c->dis);
}
