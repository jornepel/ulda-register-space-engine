/* ulda.c — implementation */
#include "ulda.h"

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
