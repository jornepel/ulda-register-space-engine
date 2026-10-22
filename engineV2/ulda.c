/* ============================================================================
 * ULDA-X28 — Base-60 Coordinate Engine (Hand Grid)
 * ============================================================================
 * The coordinate is the number of steps per scale:
 *   knuckles = 1  (the base unit, 1..12)
 *   fingers  = 12 (the hand, 1..5)
 *   macros   = 60 (the two hands, 5 x 12)
 *
 * The carry is: x12 (knuckles -> fingers), x5 (fingers -> macros).
 *
 * Order of operations (Sumerian):
 *   1. Shift  — bereken() puts the number directly on the grid.
 *   2. Matrix — add() sums the macro-coordinates.
 *   3. Carry  — everywhere.
 *
 * No floating point. Only coordinates and carry.
 *
 * Dedication: In honor of Terrence Andrew Davis (1969-2018).
 * ============================================================================
 */

#include <stdio.h>
#include <string.h>
#include <stdint.h>

typedef uint64_t u64;
typedef int64_t  i64;

/* ============================================================================
 * PART 1 — THE COORDINATE
 * ============================================================================
 */
typedef struct {
    i64 macros;    /* 1 macro = 60 */
    i64 fingers;   /* 1 finger = 12 */
    i64 knuckles;  /* 1 knuckle = 1 */
} coordinaat;

/* ============================================================================
 * PART 2 — THE CARRY (x12, x5) — with while loops
 * ============================================================================
 * Always applied after every operation. Rolls until stable.
 * ============================================================================
 */
static void carry(coordinaat *c) {
    /* borrow: resolve negative columns first */
    while (c->knuckles < 0) { c->knuckles += 12; c->fingers -= 1; }
    while (c->fingers < 0)  { c->fingers  += 5;  c->macros  -= 1; }

    /* carry: roll until stable */
    while (c->knuckles >= 12) { c->knuckles -= 12; c->fingers += 1; }
    while (c->fingers >= 5)   { c->fingers  -= 5;  c->macros  += 1; }
}

/* ============================================================================
 * PART 3 — BEREKEN (unit -> coordinate)
 * ============================================================================
 */
static coordinaat bereken(u64 eenheid) {
    coordinaat c = {0, 0, 0};
    c.macros   = (i64)(eenheid / 60);
    c.fingers  = (i64)((eenheid % 60) / 12);
    c.knuckles = (i64)((eenheid % 60) % 12);
    carry(&c);
    return c;
}

/* ============================================================================
 * PART 4 — COORDINAAT NAAR EENHEID
 * ============================================================================
 */
static u64 coordinaat_naar_eenheid(coordinaat c) {
    return (u64)(c.macros * 60 + c.fingers * 12 + c.knuckles);
}

/* ============================================================================
 * PART 5 — ADD
 * ============================================================================
 */
static coordinaat add(coordinaat a, coordinaat b) {
    coordinaat c = {
        a.macros   + b.macros,
        a.fingers  + b.fingers,
        a.knuckles + b.knuckles
    };
    carry(&c);
    return c;
}

/* ============================================================================
 * PART 6 — SUB (safe)
 * ============================================================================
 * Returns 1 on success, 0 on underflow.
 * ============================================================================
 */
static int sub(coordinaat a, coordinaat b, coordinaat *out) {
    coordinaat c = {
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
 * PART 7 — MUL
 * ============================================================================
 */
static coordinaat mul(coordinaat a, u64 n) {
    coordinaat c = {
        a.macros   * (i64)n,
        a.fingers  * (i64)n,
        a.knuckles * (i64)n
    };
    carry(&c);
    return c;
}

/* ============================================================================
 * PART 8 — DIV (via unit conversion)
 * ============================================================================
 * Returns 1 on success, 0 on division by zero.
 * ============================================================================
 */
static int div_op(coordinaat a, u64 n, coordinaat *out) {
    if (n == 0) return 0;
    *out = bereken(coordinaat_naar_eenheid(a) / n);
    return 1;
}

/* ============================================================================
 * PART 9 — WRITE
 * ============================================================================
 */
static void write_coordinaat(const coordinaat *c, char *buf, size_t size) {
    snprintf(buf, size, "(%lld, %lld, %lld)",
             (long long)c->macros,
             (long long)c->fingers,
             (long long)c->knuckles);
}

/* ============================================================================
 * PART 10 — THE TESTS
 * ============================================================================
 */
static int check(const char *name, const char *got, const char *expected) {
    int ok = (strcmp(got, expected) == 0);
    printf("%-28s got=%-18s expected=%-18s  %s\n",
           name, got, expected, ok ? "PASS" : "FAIL");
    return ok;
}

int main(void) {
    printf("ULDA-X28 — Base-60 Coordinate Engine (Hand Grid)\n");
    printf("================================================\n\n");

    int all_ok = 1;
    char buf[128];

    /* Bereken */
    coordinaat c1860 = bereken(1860);
    write_coordinaat(&c1860, buf, sizeof(buf));
    all_ok &= check("bereken(1860)", buf, "(31, 0, 0)");

    coordinaat c3600 = bereken(3600);
    write_coordinaat(&c3600, buf, sizeof(buf));
    all_ok &= check("bereken(3600)", buf, "(60, 0, 0)");

    coordinaat c4320 = bereken(4320);
    write_coordinaat(&c4320, buf, sizeof(buf));
    all_ok &= check("bereken(4320)", buf, "(72, 0, 0)");

    coordinaat c1878 = bereken(1878);
    write_coordinaat(&c1878, buf, sizeof(buf));
    all_ok &= check("bereken(1878)", buf, "(31, 1, 6)");

    /* Add */
    coordinaat som = add(c1860, c3600);
    write_coordinaat(&som, buf, sizeof(buf));
    all_ok &= check("add(1860, 3600)", buf, "(91, 0, 0)");

    /* Sub */
    coordinaat verschil;
    int ok = sub(c3600, c1860, &verschil);
    write_coordinaat(&verschil, buf, sizeof(buf));
    all_ok &= check("sub(3600, 1860)", buf, "(29, 0, 0)");
    all_ok &= (ok == 1);

    ok = sub(c1860, c3600, &verschil);
    all_ok &= (ok == 0);

    /* Mul */
    coordinaat product = mul(c1860, 2);
    write_coordinaat(&product, buf, sizeof(buf));
    all_ok &= check("mul(1860, 2)", buf, "(62, 0, 0)");

    /* Mul with carry roll */
    coordinaat product5 = mul(c1878, 5);
    write_coordinaat(&product5, buf, sizeof(buf));
    all_ok &= check("mul(1878, 5)", buf, "(156, 2, 6)");

    /* Div */
    coordinaat quotient;
    ok = div_op(c3600, 2, &quotient);
    write_coordinaat(&quotient, buf, sizeof(buf));
    all_ok &= check("div(3600, 2)", buf, "(30, 0, 0)");
    all_ok &= (ok == 1);

    ok = div_op(c3600, 0, &quotient);
    all_ok &= (ok == 0);

    printf("\n%s\n", all_ok ? "ALL TESTS PASSED" : "SOME TESTS FAILED");
    return all_ok ? 0 : 1;
}
