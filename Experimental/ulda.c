/* ============================================================================
 * ULDA-X28 — Base-60 2x5 Bare-Metal Engine (OPTIMIZED BITSHIFT VERSION)
 * ============================================================================
 * No division. No modulo. No zero. No linear loops.
 * High-speed bit-shifted subtraction pipeline for exponential throughput.
 *
 * Dedication: In honor of Terrence Andrew Davis (1969-2018)
 * Without him, we would never have continued with the mathematics.
 * ============================================================================
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
 * LOSSLESS BITSHIFT EXPONENTIAL SUBTRACTION ENGINE
 * Bypasses division hardware units entirely while wiping out 
 * linear loop latency. Operates in log-time.
 * ------------------------------------------------------------
 */
static u64 optimized_sub_mod(u64 value, u64 divisor, u64 *carries) {
    if (value < divisor) {
        if (carries) *carries = 0;
        return value;
    }

    u64 temp_divisor = divisor;
    int shift = 0;
    u64 local_carries = 0;

    // Step 1: Shift the divisor left exponentially until it hits the input boundary
    while (value >= (temp_divisor << 1)) {
        if ((temp_divisor << 1) < temp_divisor) break; // Protect 64-bit integer overflow
        temp_divisor <<= 1;
        shift++;
    }

    // Step 2: Subtract shifts out logarithmically downwards
    while (shift >= 0) {
        if (value >= temp_divisor) {
            value -= temp_divisor;
            local_carries += (1ULL << shift);
        }
        temp_divisor >>= 1;
        shift--;
    }

    if (carries) *carries = local_carries;
    return value;
}

/* ------------------------------------------------------------
 * PART 2 — THE LUM (Look-Up Logic Matrix)
 * Carry by optimized bitshift subtraction. No division, no modulo.
 * ------------------------------------------------------------
 */
void lum_carry(ulda_reg *r) {
    u64 carries = 0;
    
    r->dis  = optimized_sub_mod(r->dis, 60, &carries);
    r->ges += carries;
    
    r->ges  = optimized_sub_mod(r->ges, 60, &carries);
    r->gesu += carries;
    
    r->gesu = optimized_sub_mod(r->gesu, 60, &carries);
    r->sar += carries;
}

/* ------------------------------------------------------------
 * PART 3 — THE OPERATOR (The Omitted 6)
 * Instant operator reduction via bitshift logic.
 * ------------------------------------------------------------
 */
u64 lum_operator(u64 value) {
    return optimized_sub_mod(value, 6, (void*)0);
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
 * Locked angle steps computed in log-time.
 * ------------------------------------------------------------
 */
u32 the_lock(u64 angle) {
    u64 steps = 0;
    if (angle == 0) return 0;
    optimized_sub_mod(angle - 1, 72, &steps);
    return (u32)steps + 1;
}

/* ------------------------------------------------------------
 * PART 6 — THE CONVERSION (Base-10 -> Base-60)
 * High-speed vector parsing. Zero data loss.
 * ------------------------------------------------------------
 */
ulda_reg convert(u64 n) {
    ulda_reg r = {0, 0, 0, 0};
    u64 carries = 0;

    n = optimized_sub_mod(n, 216000, &carries);
    r.sar = carries;

    n = optimized_sub_mod(n, 3600, &carries);
    r.gesu = carries;

    n = optimized_sub_mod(n, 60, &carries);
    r.ges = carries;

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
