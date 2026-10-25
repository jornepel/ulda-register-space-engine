/* bench.c — measure the compass engine */
#define _POSIX_C_SOURCE 199309L  /* Required for clock_gettime under -std=c11 */

#include "ulda.h"
#include <stdio.h>
#include <time.h>
#include <stdint.h>

#define N    50000000
#define REPS 5

static double now_seconds(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (double)ts.tv_sec + (double)ts.tv_nsec * 1e-9;
}

/* Forces the compiler to reload v each iteration — cannot be folded. */
static vec3 volatile_src;

int main(void) {
    /* The roll-over chord: O = (0, 1, φ) to Q = (−1, −1, −1) */
    vec3 base = { {-1,0}, {-2,0}, {-1,-1} };
    volatile_src = base;

    int64_t acc = 0;   /* NOT volatile — lives in a register */

    /* Real warm-up: run the hot path with real data. */
    for (int i = 0; i < 1000000; i++) {
        vec3 v = volatile_src;
        v.x.a += i & 1;                 /* defeat CSE */
        zphi r = chord_sqnorm_vec(v);
        acc += r.a + r.b;
    }

    double best = 1e9;
    for (int rep = 0; rep < REPS; rep++) {
        acc = 0;
        double t0 = now_seconds();
        for (int i = 0; i < N; i++) {
            vec3 v = volatile_src;      /* forced reload */
            v.x.a += i & 1;             /* defeat loop-invariant hoist */
            zphi r = chord_sqnorm_vec(v);
            acc += r.a + r.b;
        }
        double t1 = now_seconds();
        double e = t1 - t0;
        if (e < best) best = e;
    }

    /* Escape acc so the whole loop can't be eliminated. */
    printf("chord_sqnorm_vec: %d iterations × %d reps (best of %d)\n",
           N, REPS, REPS);
    printf("  best total : %.4f s\n", best);
    printf("  per call   : %.2f ns\n", best * 1e9 / N);
    printf("  ~cycles    : %.1f  (at 3 GHz)\n", best * 1e9 / N * 3.0);
    printf("  throughput : %.1f M ops/s\n", N / best / 1e6);
    printf("  sink       : %lld\n", (long long)acc);
    return 0;
}
