/* ============================================================
 * ULDA-X28 — Test Harness
 * ============================================================
 * This is the visible test. It calls the engine and prints
 * the results. The engine itself remains bare metal.
 * ============================================================
 */

#include <stdio.h>

/* The engine's types and functions */
typedef unsigned long long u64;
typedef unsigned int       u32;

typedef struct {
    u64 dis;
    u64 ges;
    u64 gesu;
    u64 sar;
} ulda_reg;

extern void    lum_carry(ulda_reg *r);
extern u64     lum_operator(u64 value);
extern u64     the_gate(void);
extern u32     the_lock(u64 angle);
extern ulda_reg convert(u64 n);
extern u64     ulda_test(void);

int main(void) {
    printf("ULDA-X28 — Base-60 2x5 Engine Test\n");
    printf("==================================\n\n");

    /* Test 1: the gate */
    u64 gate = the_gate();
    printf("The gate:           %llu  (expected 11)\n", gate);

    /* Test 2: the lock */
    u32 lock = the_lock(360);
    printf("The lock (360):     %u   (expected 5)\n", lock);

    /* Test 3: the operator */
    u64 op = lum_operator(137);
    printf("Operator (137):     %llu  (expected 5)\n", op);

    /* Test 4: the conversion */
    ulda_reg r = convert(36620);
    printf("Convert (36620):    sar=%llu gesu=%llu ges=%llu dis=%llu\n",
           r.sar, r.gesu, r.ges, r.dis);
    printf("                    (expected sar=0 gesu=10 ges=10 dis=20)\n");

    /* Test 5: the carry */
    ulda_reg c = {59, 0, 0, 0};
    c.dis += 1;
    lum_carry(&c);
    printf("Carry (59+1):       dis=%llu ges=%llu\n", c.dis, c.ges);
    printf("                    (expected dis=0 ges=1)\n");

    /* The checksum */
    u64 checksum = ulda_test();
    printf("\nChecksum:           %llu  (expected 62 = 60 + 2)\n", checksum);

    return 0;
}
