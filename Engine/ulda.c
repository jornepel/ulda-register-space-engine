/* ulda.c — implementation */
#include "ulda.h"
#include <stdio.h>
#include <assert.h>

/* Hot path — the vector is already the chord. */
zphi invariant_rollover(vec3 v) {
    zphi r = chord_sqnorm_vec(v);
    assert(r.a == 7 && r.b == 3 && "rollover: v is not the antipodal chord");
    return r;
}

zphi invariant_mirror(vec3 v) {
    zphi r = chord_sqnorm_vec(v);
    assert(r.a == 3 && r.b == 1 && "mirror: v is not the mirror-plane chord");
    return r;
}

/* Structural invariants are constants of the reading. */
int64_t invariant_offset(void) { return 1; }
int64_t invariant_loop  (void) { return 5; }

void zphi_print(zphi v, char *buf, size_t size) {
    snprintf(buf, size, "%lld + %lldφ", (long long)v.a, (long long)v.b);
}

void vec3_print(vec3 v, char *buf, size_t size) {
    snprintf(buf, size,
             "(%lld+%lldφ, %lld+%lldφ, %lld+%lldφ)",
             (long long)v.x.a, (long long)v.x.b,
             (long long)v.y.a, (long long)v.y.b,
             (long long)v.z.a, (long long)v.z.b);
}
