/* ============================================================
 * ULDA-X28 — Base-60 2x5 Bare-Metal Engine
 * ============================================================
 * No division. No modulo. No zero.
 * The 6 is the operator. The 11 is the gate. The 72 is the lock.
 *
 * Dedication: In honor of Terrence Andrew Davis (1969-2018)
 * Without him, we would never have continued with the mathematics.
 * ============================================================
 */

#include <stdio.h>

typedef unsigned long long u64;
typedef unsigned int       u32;

/* ------------------------------------------------------------
 * PART 1 — THE COLUMNS
 * dis = 1, ges = 60, gesu = 3600, sar = 216000
 * ------------------------------------------------------------
 */
typedef struct {
    u64 dis;
    u64 ges;
    u64 gesu;
    u64 sar;
} ulda_reg;

/* ------------------------------------------------------------
 * PART 2 — THE LUM (Look-Up Logic Matrix)
 * Carry by subtraction. No division, no modulo.
 * ------------------------------------------------------------
 */
static void lum_carry(ulda_reg *r) {
    while (r->dis  >= 60) { r->dis  -= 60; r->ges  += 1; }
    while (r->ges  >= 60) { r->ges  -= 60; r->gesu += 1; }
    while (r->gesu >= 60) { r->gesu -= 60; r->sar  += 1; }
}

/* ------------------------------------------------------------
 * PART 3 — THE OPERATOR (The Omitted 6)
 * Subtract 6 until the value falls below 6.
 * ------------------------------------------------------------
 */
static u64 lum_operator(u64 value) {
    while (value >= 6) {
        value -= 6;
    }
    return value;
}

/* ------------------------------------------------------------
 * PART 4 — THE GATE (11)
 * 1 + 2 + 3 + 4 + 5 + 7 = 22; 22 >> 1 = 11.
 * ------------------------------------------------------------
 */
static u64 the_gate(void) {
    return (1 + 2 + 3 + 4 + 5 + 7) >> 1;
}

/* ------------------------------------------------------------
 * PART 5 — THE LOCK (72°)
 * Count 72° steps to reach the angle.
 * ------------------------------------------------------------
 */
static u32 the_lock(u64 angle) {
    u64 acc = 0;
    u32 steps = 0;
    while (acc < angle) {
        acc += 72;
        steps += 1;
    }
    return steps;
}

/* ------------------------------------------------------------
 * PART 6 — THE CONVERSION (Base-10 -> Base-60)
 * Subtraction only.
 * ------------------------------------------------------------
 */
static ulda_reg convert(u64 n) {
    ulda_reg r = {0, 0, 0, 0};

    while (n >= 216000) { n -= 216000; r.sar  += 1; }
    while (n >= 3600)   { n -= 3600;   r.gesu += 1; }
    while (n >= 60)     { n -= 60;     r.ges   += 1; }
    r.dis = n;

    return r;
}

/* ------------------------------------------------------------
 * PART 7 — THE MAIN
 * The engine, and the visible test.
 * ------------------------------------------------------------
 */
int main(void) {
    printf("ULDA-X28 — Base-60 2x5 Engine\n");
    printf("==============================\n\n");

    /* The gate */
    u64 gate = the_gate();
    printf("The gate:           %llu  (expected 11)\n", gate);

    /* The lock */
    u32 lock = the_lock(360);
    printf("The lock (360):     %u   (expected 5)\n", lock);

    /* The operator */
    u64 op = lum_operator(137);
    printf("Operator (137):     %llu  (expected 5)\n", op);

    /* The conversion */
    ulda_reg r = convert(36620);
    printf("Convert (36620):    sar=%llu gesu=%llu ges=%llu dis=%llu\n",
           r.sar, r.gesu, r.ges, r.dis);
    printf("                    (expected sar=0 gesu=10 ges=10 dis=20)\n");

    /* The carry */
    ulda_reg c = {59, 0, 0, 0};
    c.dis += 1;
    lum_carry(&c);
    printf("Carry (59+1):       dis=%llu ges=%llu\n", c.dis, c.ges);
    printf("                    (expected dis=0 ges=1)\n");

    /* The checksum */
    u64 checksum = gate + lock + op + r.gesu + r.ges + r.dis + c.ges;
    printf("\nChecksum:           %llu  (expected 62 = 60 + 2)\n", checksum);

    return 0;
}
