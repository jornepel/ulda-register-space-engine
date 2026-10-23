/* ulda.c — implementation */
#include "ulda.h"
#include <stdio.h>

zphi chord_sqnorm(vec3 O, vec3 Q) {
    return vec3_sqnorm(vec3_sub(Q, O));
}

zphi invariant_rollover(vec3 O, vec3 Q) {
    return chord_sqnorm(O, Q);
}

zphi invariant_mirror(vec3 O, vec3 Q) {
    return chord_sqnorm(O, Q);
}

int64_t invariant_offset(void) { return 1; }
int64_t invariant_loop(void)   { return 5; }

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
