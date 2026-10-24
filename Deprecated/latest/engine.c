Codepeel(57) = {steps: 7, value: 8}./* ============================================================================
 * ULDA-X28 — Base-60 Register Engine
 * ============================================================================
 * Werkversie — gebouwd volgens het goedgekeurde werkpakket.
 *
 * No floating point. No division. No modulo.
 * The walk is a rank shift with a counter. The register is the core.
 *
 * Dedication: In honor of Terrence Andrew Davis (1969-2018).
 * ============================================================================
 */

#include <stdio.h>
#include <string.h>
#include <stdint.h>

typedef uint64_t u64;

/* ============================================================================
 * PART 1 — THE REGISTER
 * ============================================================================
 * dis = 1, ges = 60, gesu = 3600, sar = 216000
 * ============================================================================
 */
typedef struct {
    u64 dis;
    u64 ges;
    u64 gesu;
    u64 sar;
} ulda_reg;

/* ============================================================================
 * PART 2 — COMPARE
 * ============================================================================
 * Compares two registers. Returns -1, 0, or 1.
 * ============================================================================
 */
static int cmp(ulda_reg a, ulda_reg b) {
    if (a.sar  != b.sar)  return (a.sar  < b.sar)  ? -1 : 1;
    if (a.gesu != b.gesu) return (a.gesu < b.gesu) ? -1 : 1;
    if (a.ges  != b.ges)  return (a.ges  < b.ges)  ? -1 : 1;
    if (a.dis  != b.dis)  return (a.dis  < b.dis)  ? -1 : 1;
    return 0;
}

/* ============================================================================
 * PART 3 — READ / WRITE
 * ============================================================================
 */
static int read_register(const char *notation, ulda_reg *r) {
    r->sar = 0; r->gesu = 0; r->ges = 0; r->dis = 0;
    return (sscanf(notation, "%llu.%llu.%llu.%llu",
                   &r->sar, &r->gesu, &r->ges, &r->dis) == 4);
}

static void write_register(const ulda_reg *r, char *out, size_t out_size) {
    snprintf(out, out_size, "%llu.%llu.%llu.%llu",
             r->sar, r->gesu, r->ges, r->dis);
}

/* ============================================================================
 * PART 4 — THE CARRY
 * ============================================================================
 */
static void carry(ulda_reg *r) {
    if (r->dis  >= 60) { r->dis  -= 60; r->ges  += 1; }
    if (r->ges  >= 60) { r->ges  -= 60; r->gesu += 1; }
    if (r->gesu >= 60) { r->gesu -= 60; r->sar  += 1; }
}

/* ============================================================================
 * PART 5 — ADD
 * ============================================================================
 */
static ulda_reg add(ulda_reg a, ulda_reg b) {
    ulda_reg out;
    out.dis  = a.dis  + b.dis;
    out.ges  = a.ges  + b.ges;
    out.gesu = a.gesu + b.gesu;
    out.sar  = a.sar  + b.sar;
    carry(&out);
    return out;
}

/* ============================================================================
 * PART 6 — SUB (safe)
 * ============================================================================
 * Returns 1 on success, 0 if a < b.
 * The borrow chains: if ges is 0, it borrows from gesu, and so on.
 * ============================================================================
 */
static int sub(ulda_reg a, ulda_reg b, ulda_reg *out) {
    if (cmp(a, b) < 0) return 0;

    *out = a;

    /* dis */
    if (out->dis < b.dis) {
        out->dis += 60;
        if (out->ges == 0) {
            out->ges += 60;
            if (out->gesu == 0) {
                out->gesu += 60;
                out->sar -= 1;
            }
            out->gesu -= 1;
        }
        out->ges -= 1;
    }
    out->dis -= b.dis;

    /* ges */
    if (out->ges < b.ges) {
        out->ges += 60;
        if (out->gesu == 0) {
            out->gesu += 60;
            out->sar -= 1;
        }
        out->gesu -= 1;
    }
    out->ges -= b.ges;

    /* gesu */
    if (out->gesu < b.gesu) {
        out->gesu += 60;
        out->sar -= 1;
    }
    out->gesu -= b.gesu;

    /* sar */
    out->sar -= b.sar;

    return 1;
}

/* ============================================================================
 * PART 7 — SHIFT LEFT (double)
 * ============================================================================
 */
static ulda_reg shift_left(ulda_reg a) {
    ulda_reg out;
    out.dis  = a.dis  * 2;
    out.ges  = a.ges  * 2;
    out.gesu = a.gesu * 2;
    out.sar  = a.sar  * 2;
    carry(&out);
    return out;
}

/* ============================================================================
 * PART 8 — MUL (shift-and-add, O(log n))
 * ============================================================================
 * 3 * (1/3) = 3 * 0.0.20.0 = 0.0.1.0 = 1 exactly.
 * ============================================================================
 */
static ulda_reg mul(ulda_reg a, u64 n) {
    ulda_reg out = {0, 0, 0, 0};
    while (n > 0) {
        if (n & 1) out = add(out, a);
        a = shift_left(a);
        n >>= 1;
    }
    return out;
}

/* ============================================================================
 * PART 9 — THE WALK
 * ============================================================================
 * Walks through odd numbers, counting steps and shifts.
 * A shift happens when the next odd number cannot be subtracted.
 *
 * walk(50, 8) = {7, 1, 46}:
 *   50-1=49, -3=46, -5=41, -7=34, -9=25, -11=14, -13=1,
 *   -15 can't → shift (1+60=61), -15=46.
 * ============================================================================
 */
typedef struct {
    u64 steps;
    u64 shifts;
    u64 value;
} ulda_walk;

static ulda_walk walk(u64 start, u64 max_steps) {
    ulda_walk w = {0, 0, start};
    u64 odd = 1;

    for (u64 i = 0; i < max_steps; i++) {
        if (w.value < odd) {
            w.shifts += 1;
            w.value += 60;   /* opschuiven */
        }
        w.value -= odd;
        w.steps += 1;
        odd += 2;
    }
    return w;
}

/* ============================================================================
 * PART 10 — THE PEEL (separate function)
 * ============================================================================
 * Walks through odd numbers, counting steps, but stops when the next
 * odd number cannot be subtracted. No shift.
 * ============================================================================
 */
static ulda_walk peel(u64 start, u64 max_steps) {
    ulda_walk w = {0, 0, start};
    u64 odd = 1;

    for (u64 i = 0; i < max_steps; i++) {
        if (w.value < odd) break;
        w.value -= odd;
        w.steps += 1;
        odd += 2;
    }
    return w;
}

/* ============================================================================
 * PART 11 — THE COMPASS
 * ============================================================================
 * A number as a coordinate in the 360° circle. No division.
 * ============================================================================
 */
typedef struct {
    u64 x, y, z;
} coord;

static coord compass(u64 angle) {
    coord c = {0, 0, 0};
    u64 a = angle;
    while (a >= 72) { a -= 72; c.x++; }
    c.y = c.x * 2;
    c.z = 0;
    return c;
}

/* ============================================================================
 * PART 12 — THE GATE
 * ============================================================================
 */
static u64 the_gate(void) {
    return (1 + 2 + 3 + 4 + 5 + 7) >> 1;
}

/* ============================================================================
 * PART 13 — THE FRACTIONS
 * ============================================================================
 */
static ulda_reg third(void) { return (ulda_reg){0, 0, 20, 0}; }
static ulda_reg sixth(void) { return (ulda_reg){0, 0, 10, 0}; }
static ulda_reg half(void)  { return (ulda_reg){0, 0, 30, 0}; }

/* ============================================================================
 * PART 14 — DOUBLE WRAPPER (compatibility only)
 * ============================================================================
 */
static double to_double(ulda_reg r) {
    return (double)r.sar * 216000.0
         + (double)r.gesu * 3600.0
         + (double)r.ges  * 60.0
         + (double)r.dis;
}

/* ============================================================================
 * PART 15 — THE TESTS
 * ============================================================================
 */
static int check(const char *name, const char *got, const char *expected) {
    int ok = (strcmp(got, expected) == 0);
    printf("%-30s got=%-12s expected=%-12s  %s\n",
           name, got, expected, ok ? "PASS" : "FAIL");
    return ok;
}

static int check_num(const char *name, u64 got, u64 expected) {
    int ok = (got == expected);
    printf("%-30s got=%-12llu expected=%-12llu  %s\n",
           name, got, expected, ok ? "PASS" : "FAIL");
    return ok;
}

int main(void) {
    printf("ULDA-X28 — Base-60 Register Engine\n");
    printf("===================================\n\n");

    int all_ok = 1;
    char buf[64];

    /* Walk */
    printf("Walk:\n");
    ulda_walk w = walk(50, 8);
    all_ok &= check_num("  walk(50,8).steps",  w.steps,  7);
    all_ok &= check_num("  walk(50,8).shifts", w.shifts, 1);
    all_ok &= check_num("  walk(50,8).value",  w.value,  46);

    /* Peel */
    printf("\nPeel:\n");
    ulda_walk p = peel(50, 8);
    all_ok &= check_num("  peel(50,8).steps",  p.steps,  7);
    all_ok &= check_num("  peel(50,8).shifts", p.shifts, 0);
    all_ok &= check_num("  peel(50,8).value",  p.value,  1);

    /* Fractions */
    printf("\nFractions:\n");
    write_register(&(ulda_reg){0,0,1,0}, buf, sizeof(buf));
    ulda_reg t3 = mul(third(), 3);
    write_register(&t3, buf, sizeof(buf));
    all_ok &= check("  3 * (1/3)", buf, "0.0.1.0");

    ulda_reg t6 = mul(sixth(), 6);
    write_register(&t6, buf, sizeof(buf));
    all_ok &= check("  6 * (1/6)", buf, "0.0.1.0");

    ulda_reg t2 = mul(half(), 2);
    write_register(&t2, buf, sizeof(buf));
    all_ok &= check("  2 * (1/2)", buf, "0.0.1.0");

    /* Add / carry */
    printf("\nAdd / carry:\n");
    ulda_reg a = {59, 0, 0, 0};
    ulda_reg b = {1, 0, 0, 0};
    ulda_reg out = add(a, b);
    write_register(&out, buf, sizeof(buf));
    all_ok &= check("  59 + 1", buf, "0.0.1.0");

    /* Sub (safe) */
    printf("\nSub (safe):\n");
    ulda_reg one = {0, 0, 1, 0};
    ulda_reg three = {3, 0, 0, 0};
    int ok = sub(one, three, &out);
    all_ok &= check_num("  sub(1,3) returns", ok, 0);

    ulda_reg one_third = third();
    ok = sub(one, one_third, &out);
    write_register(&out, buf, sizeof(buf));
    all_ok &= check("  1 - 1/3", buf, "0.0.40.0");

    /* Compass */
    printf("\nCompass:\n");
    coord c360 = compass(360);
    all_ok &= check_num("  compass(360).x", c360.x, 5);
    all_ok &= check_num("  compass(360).y", c360.y, 10);
    all_ok &= check_num("  compass(360).z", c360.z, 0);

    coord c72 = compass(72);
    all_ok &= check_num("  compass(72).x", c72.x, 1);
    all_ok &= check_num("  compass(72).y", c72.y, 2);

    /* Gate */
    printf("\nGate:\n");
    all_ok &= check_num("  the_gate()", the_gate(), 11);

    /* Double wrapper */
    printf("\nDouble wrapper:\n");
    double d_third = to_double(one_third);
    double d_three = to_double(mul(one_third, 3));
    printf("  1/3 in double:       %.20f\n", d_third);
    printf("  3 * (1/3) in double: %.20f\n", d_three);
    all_ok &= check_num("  double 3*(1/3)==1", (u64)(d_three == 1.0), 1);

    printf("\n%s\n", all_ok ? "ALL TESTS PASSED" : "SOME TESTS FAILED");
    return all_ok ? 0 : 1;
}
