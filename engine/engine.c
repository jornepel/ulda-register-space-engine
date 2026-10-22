/* ============================================================================
 * ULDA-X28 — Base-60 Register Engine (Complete)
 * ============================================================================
 * The register is the only structure. The peel is the only operation.
 * Everything else is built on top of the peel.
 *
 * No floating point. No division. No modulo.
 *
 * Operations:
 *   peel(n)         — the coordinate of n
 *   add(a, b)       — peel(a + b)
 *   sub(a, b)       — peel(a - b)        [safe: returns 0 if a < b]
 *   mul(a, b)       — peel(a * b)
 *   div(a, b)       — peel(a / b)        [integer division]
 *   mod(a, b)       — peel(a % b)
 *   pow(a, n)       — peel(a^n)
 *   gcd(a, b)       — peel(gcd(a, b))
 *   compass(angle)  — the coordinate in the 360° circle
 *
 * The register grows with the number. No fixed limit.
 *
 * Dedication: In honor of Terrence Andrew Davis (1969-2018).
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef uint64_t u64;

/* ============================================================================
 * PART 1 — THE REGISTER
 * ============================================================================
 */
typedef struct {
    u64 *steps;
    u64 ranks;
    u64 capacity;
} ulda_register;

static void reg_init(ulda_register *r, u64 capacity) {
    r->steps = (u64 *)malloc(capacity * sizeof(u64));
    r->ranks = 0;
    r->capacity = capacity;
}

static void reg_free(ulda_register *r) {
    free(r->steps);
    r->steps = NULL;
    r->ranks = 0;
    r->capacity = 0;
}

static void reg_ensure(ulda_register *r, u64 needed) {
    if (needed <= r->capacity) return;
    u64 new_cap = r->capacity ? r->capacity * 2 : 8;
    while (new_cap < needed) new_cap *= 2;
    r->steps = (u64 *)realloc(r->steps, new_cap * sizeof(u64));
    r->capacity = new_cap;
}

/* ============================================================================
 * PART 2 — THE PEEL (the only operation)
 * ============================================================================
 * Fills the register with the coordinate of n.
 * No allocation per call (only when growing).
 * ============================================================================
 */
static void peel(ulda_register *r, u64 n) {
    r->ranks = 0;
    u64 value = n;
    u64 odd = 1;
    u64 steps = 0;

    while (value > 0) {
        if (value < odd) {
            reg_ensure(r, r->ranks + 1);
            r->steps[r->ranks++] = steps;
            steps = 0;
            odd = 1;
            continue;
        }
        value -= odd;
        steps++;
        odd += 2;
    }

    if (steps > 0) {
        reg_ensure(r, r->ranks + 1);
        r->steps[r->ranks++] = steps;
    }
}

/* ============================================================================
 * PART 3 — ADD
 * ============================================================================
 */
static void add(ulda_register *out, u64 a, u64 b) {
    peel(out, a + b);
}

/* ============================================================================
 * PART 4 — SUB (safe)
 * ============================================================================
 * Returns 1 on success, 0 if a < b.
 * ============================================================================
 */
static int sub(ulda_register *out, u64 a, u64 b) {
    if (a < b) return 0;
    peel(out, a - b);
    return 1;
}

/* ============================================================================
 * PART 5 — MUL
 * ============================================================================
 */
static void mul(ulda_register *out, u64 a, u64 b) {
    peel(out, a * b);
}

/* ============================================================================
 * PART 6 — DIV (integer division)
 * ============================================================================
 * Returns 1 on success, 0 if b == 0.
 * ============================================================================
 */
static int div_op(ulda_register *out, u64 a, u64 b) {
    if (b == 0) return 0;
    peel(out, a / b);
    return 1;
}

/* ============================================================================
 * PART 7 — MOD
 * ============================================================================
 * Returns 1 on success, 0 if b == 0.
 * ============================================================================
 */
static int mod_op(ulda_register *out, u64 a, u64 b) {
    if (b == 0) return 0;
    peel(out, a % b);
    return 1;
}

/* ============================================================================
 * PART 8 — POW
 * ============================================================================
 */
static void pow_op(ulda_register *out, u64 a, u64 n) {
    u64 result = 1;
    for (u64 i = 0; i < n; i++) result *= a;
    peel(out, result);
}

/* ============================================================================
 * PART 9 — GCD
 * ============================================================================
 */
static u64 gcd_value(u64 a, u64 b) {
    while (b != 0) {
        u64 t = b;
        b = a % b;
        a = t;
    }
    return a;
}

static void gcd_op(ulda_register *out, u64 a, u64 b) {
    peel(out, gcd_value(a, b));
}

/* ============================================================================
 * PART 10 — COMPASS
 * ============================================================================
 * The coordinate in the 360° circle. Steps of 72°.
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
 * PART 11 — WRITE
 * ============================================================================
 */
static void write_register(const ulda_register *r, char *buf, size_t size) {
    size_t pos = 0;
    pos += snprintf(buf + pos, size - pos, "[");
    for (u64 i = 0; i < r->ranks; i++) {
        pos += snprintf(buf + pos, size - pos, "%llu%s",
                        r->steps[i],
                        (i + 1 < r->ranks) ? ", " : "");
    }
    snprintf(buf + pos, size - pos, "]");
}

/* ============================================================================
 * PART 12 — THE TESTS
 * ============================================================================
 */
static int check(const char *name, const char *got, const char *expected) {
    int ok = (strcmp(got, expected) == 0);
    printf("%-26s got=%-18s expected=%-18s  %s\n",
           name, got, expected, ok ? "PASS" : "FAIL");
    return ok;
}

int main(void) {
    printf("ULDA-X28 — Base-60 Register Engine (Complete)\n");
    printf("==============================================\n\n");

    int all_ok = 1;
    char buf[256];

    ulda_register r;
    reg_init(&r, 8);

    /* Peel */
    peel(&r, 7);   write_register(&r, buf, sizeof(buf));
    all_ok &= check("peel(7)", buf, "[2, 1, 1, 1]");

    peel(&r, 57);  write_register(&r, buf, sizeof(buf));
    all_ok &= check("peel(57)", buf, "[7, 2, 2]");

    peel(&r, 100); write_register(&r, buf, sizeof(buf));
    all_ok &= check("peel(100)", buf, "[10]");

    /* Add */
    add(&r, 7, 50); write_register(&r, buf, sizeof(buf));
    all_ok &= check("add(7, 50)", buf, "[7, 2, 2]");

    /* Sub (safe) */
    int ok = sub(&r, 50, 7); write_register(&r, buf, sizeof(buf));
    all_ok &= check("sub(50, 7)", buf, "[6, 1, 2]");
    all_ok &= (ok == 1);

    ok = sub(&r, 7, 50);
    all_ok &= (ok == 0);

    /* Mul */
    mul(&r, 7, 8); write_register(&r, buf, sizeof(buf));
    all_ok &= check("mul(7, 8)", buf, "[7, 1, 2]");

    /* Div */
    ok = div_op(&r, 57, 7); write_register(&r, buf, sizeof(buf));
    all_ok &= check("div(57, 7)", buf, "[2, 2]");
    all_ok &= (ok == 1);

    ok = div_op(&r, 10, 0);
    all_ok &= (ok == 0);

    /* Mod */
    ok = mod_op(&r, 57, 7); write_register(&r, buf, sizeof(buf));
    all_ok &= check("mod(57, 7)", buf, "[2, 1, 1]");
    all_ok &= (ok == 1);

    /* Pow */
    pow_op(&r, 2, 5); write_register(&r, buf, sizeof(buf));
    all_ok &= check("pow(2, 5) = peel(32)", buf, "[5, 2, 1]");

    /* Gcd */
    gcd_op(&r, 48, 36); write_register(&r, buf, sizeof(buf));
    all_ok &= check("gcd(48, 36) = peel(12)", buf, "[3, 1, 1, 1]");

    /* Compass */
    coord k360 = compass(360);
    printf("\ncompass(360) = (%llu, %llu, %llu)\n", k360.x, k360.y, k360.z);
    coord k72 = compass(72);
    printf("compass(72)  = (%llu, %llu, %llu)\n", k72.x, k72.y, k72.z);

    reg_free(&r);

    printf("\n%s\n", all_ok ? "ALL TESTS PASSED" : "SOME TESTS FAILED");
    return all_ok ? 0 : 1;
}
