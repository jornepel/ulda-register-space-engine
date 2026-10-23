/* ulda.c — ULDA Topological Decoder Engine */
#include "ulda.h"
#include <stdio.h>

/* ============================================================================
 * PART 1 — THE CAY & BORROW MATRIX (Synchronized Radix Grid)
 * ============================================================================
 * Aligned to the exact divisors of the multi-base precessional ladder:
 * dis (6) -> u (10) -> full_macro (10) -> sar (10) -> saru (6) -> sar_gal (60)
 * ============================================================================
 */
void carry(coordinate *c) {
    /* Step 1: Flatten and cascade borrows from the lowest column upward */
    while (c->dis < 0) { c->dis += 6; c->u -= 1; }
    while (c->u < 0) { c->u += 10; c->full_macro -= 1; }
    while (c->full_macro < 0) { c->full_macro += 10; c->sar -= 1; }
    while (c->sar < 0) { c->sar += 10; c->saru -= 1; }
    while (c->saru < 0) { c->saru += 6; c->sar_gal -= 1; }
    while (c->sar_gal < 0) { c->sar_gal += 60; c->sar_gal_shu_nu_tag_ga -= 1; }

    /* Step 2: Cascade carries from the lowest column upward */
    if (c->dis >= 6) {
        c->u += c->dis / 6;
        c->dis %= 6;
    }
    if (c->u >= 10) {
        c->full_macro += c->u / 10;
        c->u %= 10;
    }
    if (c->full_macro >= 10) {
        c->sar += c->full_macro / 10;
        c->full_macro %= 10;
    }
    if (c->sar >= 10) {
        c->saru += c->sar / 10;
        c->sar %= 10;
    }
    if (c->saru >= 6) {
        c->sar_gal += c->saru / 6;
        c->saru %= 6;
    }
    if (c->sar_gal >= 60) {
        c->sar_gal_shu_nu_tag_ga += c->sar_gal / 60;
        c->sar_gal %= 60;
    }
}

/* ============================================================================
 * PART 2 — CALCULATE (unit -> coordinate)
 * ============================================================================
 */
coordinate calculate(u64 unit) {
    coordinate c = {0, 0, 0, 0, 0, 0, 0};
    c.sar_gal_shu_nu_tag_ga = (i64)(unit / 12960000LL); unit %= 12960000LL;
    c.sar_gal               = (i64)(unit / 216000LL);   unit %= 216000LL;
    c.saru                  = (i64)(unit / 36000LL);    unit %= 36000LL;
    c.sar                   = (i64)(unit / 3600LL);     unit %= 3600LL;
    c.full_macro            = (i64)(unit / 360LL);      unit %= 360LL;
    c.u                     = (i64)(unit / 36LL);       unit %= 36LL;
    c.dis                   = (i64)(unit / 6LL);        unit %= 6LL;
    
    /* Remaining base units are captured within the dis fraction space */
    carry(&c);
    return c;
}

/* ============================================================================
 * PART 3 — COORDINATE TO UNIT
 * ============================================================================
 */
u64 coordinate_to_unit(coordinate c) {
    return (u64)(
        c.sar_gal_shu_nu_tag_ga * 12960000LL +
        c.sar_gal               * 216000LL +
        c.saru                  * 36000LL +
        c.sar                   * 3600LL +
        c.full_macro            * 360LL +
        c.u                     * 36LL +
        c.dis                   * 6LL
    );
}

/* ============================================================================
 * PART 4 — ADD
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
    carry(&c);
    return c;
}

/* ============================================================================
 * PART 5 — SUBTRACT (safe)
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
    carry(&c);
    if (c.sar_gal_shu_nu_tag_ga < 0) return 0;
    *out = c;
    return 1;
}

/* ============================================================================
 * PART 6 — MULTIPLY
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
    carry(&c);
    return c;
}

/* ============================================================================
 * PART 7 — DIVIDE (via unit conversion)
 * ============================================================================
 */
int divide(coordinate a, u64 n, coordinate *out) {
    if (n == 0) return 0;
    *out = calculate(coordinate_to_unit(a) / n);
    return 1;
}

/* ============================================================================
 * PART 8 — WRITE
 * ============================================================================
 */
void write_coordinate(const coordinate *c, char *buf, size_t size) {
    snprintf(buf, size, "(%lld, %lld, %lld, %lld, %lld, %lld, %lld)",
             (long long)c->sar_gal_shu_nu_tag_ga,
             (long long)c->sar_gal,
             (long long)c->saru,
             (long long)c->sar,
             (long long)c->full_macro,
             (long long)c->u,
             (long long)c->dis);
}
