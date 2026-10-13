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
void lum_carry(ulda_reg *r) {
    while (r->dis  >= 60) { r->dis  -= 60; r->ges  += 1; }
    while (r->ges  >= 60) { r->ges  -= 60; r->gesu += 1; }
    while (r->gesu >= 60) { r->gesu -= 60; r->sar  += 1; }
}

/* ------------------------------------------------------------
 * PART 3 — THE OPERATOR (The Omitted 6)
 * Subtract 6 until the value falls below 6.
 * ------------------------------------------------------------
 */
u64 lum_operator(u64 value) {
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
u64 the_gate(void) {
    return (1 + 2 + 3 + 4 + 5 + 7) >> 1;
}

/* ------------------------------------------------------------
 * PART 5 — THE LOCK (72°)
 * Count 72° steps to reach the angle.
 * ------------------------------------------------------------
 */
u32 the_lock(u64 angle) {
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
ulda_reg convert(u64 n) {
    ulda_reg r = {0, 0, 0, 0};

    while (n >= 216000) { n -= 216000; r.sar  += 1; }
    while (n >= 3600)   { n -= 3600;   r.gesu += 1; }
    while (n >= 60)     { n -= 60;     r.ges   += 1; }
    r.dis = n;

    return r;
}

/* ------------------------------------------------------------
 * PART 7 — THE TEST
 * Checksum on the 36,620 invariant.
 * ------------------------------------------------------------
 */
u64 ulda_test(void) {
    u64 gate  = the_gate();          /* 11 */
    u32 lock  = the_lock(360);       /* 5  */
    u64 op    = lum_operator(137);   /* 5  */
    ulda_reg r = convert(36620);     /* sar=0, gesu=10, ges=10, dis=20 */

    ulda_reg c = {59, 0, 0, 0};
    c.dis += 1;                      /* 60 */
    lum_carry(&c);                   /* dis=0, ges=1 */

    return gate + lock + op + r.gesu + r.ges + r.dis + c.ges;
    /* 11 + 5 + 5 + 10 + 10 + 20 + 1 = 62 */
}
