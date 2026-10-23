/* test.c — verify the invariants */
#include "ulda.h"
#include <stdio.h>
#include <assert.h>

/* observer O = (0, 1, φ) */
static vec3 O_rollover(void) {
    return (vec3){ zphi_make(0,0), zphi_make(1,0), zphi_make(0,1) };
}

/* antipodal vertex Q = (−1, −1, −1) */
static vec3 Q_antipode(void) {
    return (vec3){ zphi_make(-1,0), zphi_make(-1,0), zphi_make(-1,0) };
}

/* mirror-axis observer O = (1, φ, 0) */
static vec3 O_mirror(void) {
    return (vec3){ zphi_make(1,0), zphi_make(0,1), zphi_make(0,0) };
}

/* mirror-plane vertex Q = (0, φ−1, φ) */
static vec3 Q_mirror(void) {
    return (vec3){ zphi_make(0,0), zphi_make(-1,1), zphi_make(0,1) };
}

static int zphi_eq(zphi u, zphi v) { return u.a == v.a && u.b == v.b; }

int main(void) {
    zphi r = invariant_rollover(O_rollover(), Q_antipode());
    assert(zphi_eq(r, zphi_make(7,3)));
    printf("roll-over : %lld + %lldφ  (expect 7 + 3φ)\n", (long long)r.a, (long long)r.b);

    zphi m = invariant_mirror(O_mirror(), Q_mirror());
    assert(zphi_eq(m, zphi_make(3,1)));
    printf("mirror    : %lld + %lldφ  (expect 3 + φ)\n", (long long)m.a, (long long)m.b);

    assert(invariant_offset() == 1);
    printf("offset    : %lld  (expect 1)\n", (long long)invariant_offset());

    assert(invariant_loop() == 5);
    printf("loop      : %lld  (expect 5)\n", (long long)invariant_loop());

    printf("all invariants check out\n");
    return 0;
}
