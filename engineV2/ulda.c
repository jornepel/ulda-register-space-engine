/* ulda.c — ULDA Topological Decoder Engine */
#include "ulda.h"
#include <stdio.h>

/* ============================================================================
 * PART 1 — THE CARRY (x6, x10, x10, x10, x6, x60) — with while loops
 * ============================================================================
 * Always applied after every operation. Rolls until stable.
 * ============================================================================
 */
void carry(coordinate *c) {
    /* borrow: resolve negative columns first */
    while (c->dis < 0)                  { c->dis  += 6;  c->u     -= 1; }
    while (c->u < 0)                    { c->u    += 6;  c->full_macro -= 1; }
    while (c->full_macro < 0)           { c->full_macro += 10; c->sar -= 1; }
    while (c->sar < 0)                  { c->sar  += 10; c->saru  -= 1; }
    while (c->saru < 0)                 { c->saru += 10; c->sar_gal -= 1; }
    while (c->sar_gal < 0)              { c->sar_gal += 6; c->sar_gal_shu_nu_tag_ga -= 1; }
    while (c->sar_gal_shu_nu_tag_ga < 0){ c->sar_gal_shu_nu_tag_ga += 60; }

    /* carry: roll until stable */
    while (c->dis >= 6)                 { c->dis  -= 6;  c->u     += 1; }
    while (c->u >= 6)                   { c->u    -= 6;  c->full_macro += 1; }
    while (c->full_macro >= 10)         { c->full_macro -= 10; c->sar += 1; }
    while (c->sar >= 10)                { c->sar  -= 10; c->saru  += 1; }
    while (c->saru >= 10)               { c->saru -= 10; c->sar_gal += 1; }
    while (c->sar_gal >= 6)             { c->sar_gal -= 6; c->sar_gal_shu_nu_tag_ga += 1; }
    while (c->sar_gal_shu_nu_tag_ga >= 60) { c->sar_gal_shu_nu_tag_ga -= 60; }
}

/* ============================================================================
 * PART 2 — CALCULATE (unit -> coordinate)
 * ============================================================================
 */
coordinate calculate(u64 unit) {
    coordinate c = {0, 0, 0, 0, 0, 0, 0};
    c.sar_gal_shu_nu_tag_ga = (i64)(unit / 12960000); unit %= 12960000;
    c.sar_gal               = (i64)(unit / 216000);   unit %= 216000;
    c.saru                  = (i64)(unit / 36000);    unit %= 36000;
    c.sar                   = (i64)(unit / 3600);     unit %= 3600;
    c.full_macro            = (i64)(unit / 360);      unit %= 360;
    c.u                     = (i64)(unit / 36);       unit %= 36;
    c.dis                   = (i64)(unit / 6);        unit %= 6;
    /* remainder is the unit itself */
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
