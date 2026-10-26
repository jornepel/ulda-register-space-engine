/* test.c — verify the invariants against §8 */
#include "ulda.h"
#include "puzzles.h"
#include <stdio.h>
#include <assert.h>

static int zphi_eq(zphi u, zphi v) { return u.a == v.a && u.b == v.b; }

static const char *reading_name(reading_t r) {
    switch (r) {
        case READING_ROLLOVER: return "roll-over";
        case READING_MIRROR:   return "mirror axis";
        case READING_LOOP:     return "closed loop";
        case READING_OFFSET:   return "offset";
        /* no default: -Wswitch flags any new reading_t case */
    }
    return "?";
}

int main(void) {
    /* 1. Roll-over invariant: antipodal chord from (0,1,φ) to (−1,−1,−1). */
    vec3 O = { {0,0}, {1,0}, {0,1} };
    vec3 Q = { {-1,0}, {-1,0}, {-1,0} };
    zphi v = vec3_sub(Q, O);
    zphi r = invariant_rollover(v);
    assert(zphi_eq(r, zphi_make(7,3)));
    printf("roll-over : %lld + %lldφ  (expect 7 + 3φ)\n",
           (long long)r.a, (long long)r.b);

    /* 2. Mirror invariant: mirror-plane vertex (0,φ−1,φ) from (1,φ,0). */
    vec3 Om = { {1,0}, {0,1}, {0,0} };
    vec3 Qm = { {0,0}, {-1,1}, {0,1} };
    zphi vm = vec3_sub(Qm, Om);
    zphi m = invariant_mirror(vm);
    assert(zphi_eq(m, zphi_make(3,1)));
    printf("mirror    : %lld + %lldφ  (expect 3 + φ)\n",
           (long long)m.a, (long long)m.b);

    /* 3. Structural invariants. */
    assert(invariant_offset() == 1);
    assert(invariant_loop() == 5);
    printf("offset    : %lld  (expect 1)\n", (long long)invariant_offset());
    printf("loop      : %lld  (expect 5)\n", (long long)invariant_loop());

    /* 4. All 12 puzzles pass the anchor-rank test. */
    printf("\npuzzle assignments:\n");
    for (int i = 0; i < 12; i++) {
        const puzzle *p = &PUZZLES[i];
        int shift = 0;
        switch (p->reading) {
            case READING_ROLLOVER: shift = -2; break;
            case READING_MIRROR:   shift = -1; break;
            case READING_LOOP:     shift =  0; break;
            case READING_OFFSET:   shift = +1; break;
            /* no default: see reading_name() */
        }
        int anchor = (reading_type(p->reading) == METRIC) ? 2 : 1;
        int target = anchor + shift;
        assert(target >= 0 && target <= 2);
        printf("  %-16s %-12s  anchor %d + shift %+d = %d\n",
               p->name, reading_name(p->reading), anchor, shift, target);
    }

    /* 5. Anchor-rank test passes for all 12. */
    printf("\nall 12 puzzles pass the anchor-rank test\n");
    printf("all invariants check out\n");
    return 0;
}
