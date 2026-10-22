/* ulda.c — ULDA Topological Decoder Engine */
#include "ulda.h"
#include <stdio.h>

/* ============================================================================
 * PART 1 — THE CARRY (x12, x5) — with while loops
 * ============================================================================
 * Always applied after every operation. Rolls until stable.
 * ============================================================================
 */
void carry(coordinaat *c) {
    /* borrow: resolve negative columns first */
    while (c->kootjes < 0) { c->kootjes += 12; c->vingers -= 1; }
    while (c->vingers < 0) { c->vingers += 5;  c->macros  -= 1; }

    /* carry: roll until stable */
    while (c->kootjes >= 12) { c->kootjes -= 12; c->vingers += 1; }
    while (c->vingers >= 5)  { c->vingers -= 5;  c->macros  += 1; }
}

/* ============================================================================
 * PART 2 — BEREKEN (unit -> coordinate)
 * ============================================================================
 */
coordinaat bereken(u64 eenheid) {
    coordinaat c = {0, 0, 0};
    c.macros  = (i64)(eenheid / 60);
    c.vingers = (i64)((eenheid % 60) / 12);
    c.kootjes = (i64)((eenheid % 60) % 12);
    carry(&c);
    return c;
}

/* ============================================================================
 * PART 3 — COORDINAAT NAAR EENHEID
 * ============================================================================
 */
u64 coordinaat_naar_eenheid(coordinaat c) {
    return (u64)(c.macros * 60 + c.vingers * 12 + c.kootjes);
}

/* ============================================================================
 * PART 4 — ADD
 * ============================================================================
 */
coordinaat add(coordinaat a, coordinaat b) {
    coordinaat c = {
        a.macros  + b.macros,
        a.vingers + b.vingers,
        a.kootjes + b.kootjes
    };
    carry(&c);
    return c;
}

/* ============================================================================
 * PART 5 — SUB (safe)
 * ============================================================================
 */
int sub(coordinaat a, coordinaat b, coordinaat *out) {
    coordinaat c = {
        a.macros  - b.macros,
        a.vingers - b.vingers,
        a.kootjes - b.kootjes
    };
    carry(&c);
    if (c.macros < 0) return 0;
    *out = c;
    return 1;
}

/* ============================================================================
 * PART 6 — MUL
 * ============================================================================
 */
coordinaat mul(coordinaat a, u64 n) {
    coordinaat c = {
        a.macros  * (i64)n,
        a.vingers * (i64)n,
        a.kootjes * (i64)n
    };
    carry(&c);
    return c;
}

/* ============================================================================
 * PART 7 — DIV (via unit conversion)
 * ============================================================================
 */
int div_op(coordinaat a, u64 n, coordinaat *out) {
    if (n == 0) return 0;
    *out = bereken(coordinaat_naar_eenheid(a) / n);
    return 1;
}

/* ============================================================================
 * PART 8 — WRITE
 * ============================================================================
 */
void write_coordinaat(const coordinaat *c, char *buf, size_t size) {
    snprintf(buf, size, "(%lld, %lld, %lld)",
             (long long)c->macros,
             (long long)c->vingers,
             (long long)c->kootjes);
}
