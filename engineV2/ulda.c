/* ulda.c — ULDA Topological Decoder Engine */
#include "ulda.h"
#include <stdio.h>

/* ============================================================================
 * PART 1 — THE CARRY (x12, x5) — with while loops
 * ============================================================================
 * Always applied after every operation. Rolls until stable.
 * ============================================================================
 */
void carry(coordinate *c) {
    /* borrow: resolve negative columns first */
    while (c->knuckles < 0) { c->knuckles += 12; c->fingers -= 1; }
    while (c->fingers < 0)  { c->fingers  += 5;  c->macros  -= 1; }

    /* carry: roll until stable */
    while (c->knuckles >= 12) { c->knuckles -= 12; c->fingers += 1; }
    while (c->fingers >= 5)   { c->fingers  -= 5;  c->macros  += 1; }
}

/* ============================================================================
 * PART 2 — CALCULATE (unit -> coordinate)
 * ============================================================================
 */
coordinate calculate(u64 unit) {
    coordinate c = {0, 0, 0};
    c.macros   = (i64)(unit / 60);
    c.fingers  = (i64)((unit % 60) / 12);
    c.knuckles = (i64)((unit % 60) % 12);
    carry(&c);
    return c;
}

/* ============================================================================
 * PART 3 — COORDINATE TO UNIT
 * ============================================================================
 */
u64 coordinate_to_unit(coordinate c) {
    return (u64)(c.macros * 60 + c.fingers * 12 + c.knuckles);
}

/* ============================================================================
 * PART 4 — ADD
 * ============================================================================
 */
coordinate add(coordinate a, coordinate b) {
    coordinate c = {
        a.macros   + b.macros,
        a.fingers  + b.fingers,
        a.knuckles + b.knuckles
    };
    carry(&c);
    return c;
}

/* ============================================================================
 * PART 5 — SUBTRACT (safe)
 * ============================================================================
 * Returns 1 on success, 0 on underflow.
 * ============================================================================
 */
int subtract(coordinate a, coordinate b, coordinate *out) {
    coordinate c = {
        a.macros   - b.macros,
        a.fingers  - b.fingers,
        a.knuckles - b.knuckles
    };
    carry(&c);
    if (c.macros < 0) return 0;
    *out = c;
    return 1;
}

/* ============================================================================
 * PART 6 — MULTIPLY
 * ============================================================================
 */
coordinate multiply(coordinate a, u64 n) {
    coordinate c = {
        a.macros   * (i64)n,
        a.fingers  * (i64)n,
        a.knuckles * (i64)n
    };
    carry(&c);
    return c;
}

/* ============================================================================
 * PART 7 — DIVIDE (via unit conversion)
 * ============================================================================
 * Returns 1 on success, 0 on division by zero.
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
    snprintf(buf, size, "(%lld, %lld, %lld)",
             (long long)c->macros,
             (long long)c->fingers,
             (long long)c->knuckles);
}
