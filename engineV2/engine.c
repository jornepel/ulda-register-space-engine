/* ============================================================================
 * ULDA-X28 — Base-60 Coordinate Engine (Complete)
 * ============================================================================
 * The coordinate is the number of steps per scale.
 * The ladder is: 6 -> 60 -> 360 -> 3600 -> 36000.
 * The carry is: x6, x10, x6, x10.
 *
 * Order of operations (Sumerian):
 *   1. Shift  — bereken() puts the number directly on the grid.
 *   2. Matrix — add() sums the macro-coordinates.
 *   3. Carry  — everywhere.
 *
 * Division is not column-by-column. Convert to unit, divide, convert back.
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
    i64 s36000;
    i64 s3600;
    i64 s360;
    i64 s60;
    i64 s6;
} coordinaat;

/* ============================================================================
 * PART 2 — THE CARRY (x6, x10, x6, x10) — with borrow
 * ============================================================================
 * Always applied after every operation. This is the Sumerian shift.
 * ============================================================================
 */
static void carry(coordinaat *c) {
    /* borrow: resolve negative columns first */
    while (c->s6    < 0) { c->s6    += 6;  c->s60    -= 1; }
    while (c->s60   < 0) { c->s60   += 10; c->s360   -= 1; }
    while (c->s360  < 0) { c->s360  += 6;  c->s3600  -= 1; }
    while (c->s3600 < 0) { c->s3600 += 10; c->s36000 -= 1; }

    /* carry: shift to the next macro-column */
    if (c->s6    >= 6)  { c->s6    -= 6;  c->s60    += 1; }
    if (c->s60   >= 10) { c->s60   -= 10; c->s360   += 1; }
    if (c->s360  >= 6)  { c->s360  -= 6;  c->s3600  += 1; }
    if (c->s3600 >= 10) { c->s3600 -= 10; c->s36000 += 1; }
}

/* ============================================================================
 * PART 3 — BEREKEN (unit -> coordinate) — the shift phase
 * ============================================================================
 */
static coordinaat bereken(u64 eenheid) {
    coordinaat c = {0, 0, 0, 0, 0};
    c.s36000 = (i64)(eenheid / 36000);
    c.s3600  = (i64)((eenheid % 36000) / 3600);
    c.s360   = (i64)((eenheid % 3600) / 360);
    c.s60    = (i64)((eenheid % 360) / 60);
    c.s6     = (i64)((eenheid % 60) / 6);
    carry(&c);
    return c;
}

/* ============================================================================
 * PART 4 — COORDINAAT NAAR EENHEID
 * ============================================================================
 */
static u64 coordinaat_naar_eenheid(coordinaat c) {
    return (u64)c.s36000 * 36000
         + (u64)c.s3600  * 3600
         + (u64)c.s360   * 360
         + (u64)c.s60    * 60
         + (u64)c.s6     * 6;
}

/* ============================================================================
 * PART 5 — ADD — the matrix phase
 * ============================================================================
 */
static coordinaat add(coordinaat a, coordinaat b) {
    coordinaat c = {
        a.s36000 + b.s36000,
        a.s3600  + b.s3600,
        a.s360   + b.s360,
        a.s60    + b.s60,
        a.s6     + b.s6
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
        a.s36000 - b.s36000,
        a.s3600  - b.s3600,
        a.s360   - b.s360,
        a.s60    - b.s60,
        a.s6     - b.s6
    };
    carry(&c);
    if (c.s36000 < 0) return 0;
    *out = c;
    return 1;
}

/* ============================================================================
 * PART 7 — MUL
 * ============================================================================
 */
static coordinaat mul(coordinaat a, u64 n) {
    coordinaat c = {
        a.s36000 * (i64)n,
        a.s3600  * (i64)n,
        a.s360   * (i64)n,
        a.s60    * (i64)n,
        a.s6     * (i64)n
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
    snprintf(buf, size, "(%lld, %lld, %lld, %lld, %lld)",
             (long long)c->s36000, (long long)c->s3600,
             (long long)c->s360,   (long long)c->s60,
             (long long)c->s6);
}

/* ============================================================================
 * PART 10 — THE TESTS
 * ============================================================================
 */
static int check(const char *name, const char *got, const char *expected) {
    int ok = (strcmp(got, expected) == 0);
    printf("%-28s got=%-28s expected=%-28s  %s\n",
           name, got, expected, ok ? "PASS" : "FAIL");
    return ok;
}

int main(void) {
    printf("ULDA-X28 — Base-60 Coordinate Engine (Complete)\n");
    printf("===============================================\n\n");

    int all_ok = 1;
    char buf[128];

    /* Shift phase — bereken */
    coordinaat c1860 = bereken(1860);
    write_coordinaat(&c1860, buf, sizeof(buf));
    all_ok &= check("bereken(1860)", buf, "(0, 0, 5, 1, 0)");

    coordinaat c3600 = bereken(3600);
    write_coordinaat(&c3600, buf, sizeof(buf));
    all_ok &= check("bereken(3600)", buf, "(0, 1, 0, 0, 0)");

    coordinaat c4320 = bereken(4320);
    write_coordinaat(&c4320, buf, sizeof(buf));
    all_ok &= check("bereken(4320)", buf, "(0, 1, 2, 0, 0)");

    /* Matrix phase — add */
    coordinaat som = add(c1860, c3600);
    write_coordinaat(&som, buf, sizeof(buf));
    all_ok &= check("add(1860, 3600)", buf, "(0, 1, 5, 1, 0)");

    /* Sub */
    coordinaat verschil;
    int ok = sub(c4320, c1860, &verschil);
    write_coordinaat(&verschil, buf, sizeof(buf));
    all_ok &= check("sub(4320, 1860)", buf, "(0, 0, 2, 9, 0)");
    all_ok &= (ok == 1);

    ok = sub(c1860, c4320, &verschil);
    all_ok &= (ok == 0);

    /* Mul */
    coordinaat product = mul(c1860, 2);
    write_coordinaat(&product, buf, sizeof(buf));
    all_ok &= check("mul(1860, 2)", buf, "(0, 1, 4, 2, 0)");

    /* Div */
    coordinaat quotient;
    ok = div_op(c3600, 2, &quotient);
    write_coordinaat(&quotient, buf, sizeof(buf));
    all_ok &= check("div(3600, 2)", buf, "(0, 0, 5, 0, 0)");
    all_ok &= (ok == 1);

    ok = div_op(c3600, 0, &quotient);
    all_ok &= (ok == 0);

    printf("\n%s\n", all_ok ? "ALL TESTS PASSED" : "SOME TESTS FAILED");
    return all_ok ? 0 : 1;
}
