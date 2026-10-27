/* bench.c — measure the compass engine */
#define _POSIX_C_SOURCE 199309L

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

static vec3 volatile_src;

/* Primitive-only bench: mutate x.a to defeat CSE and hoisting.
 * NOTE: resulting chord is not the §8 chord — this measures
 * the hot primitive, not invariant_rollover. */
static void bench_primitive(void) {
    int64_t acc = 0;
    double best = 1e9;
    for (int rep = 0; rep < REPS; rep++) {
        acc = 0;
        double t0 = now_seconds();
        for (int i = 0; i < N; i++) {
            vec3 v = volatile_src;
            v.x.a += i & 1;
            zphi r = chord_sqnorm_vec(v);
            acc += r.a + r.b;
        }
        double t1 = now_seconds();
        double e = t1 - t0;
        if (e < best) best = e;
    }
    printf("chord_sqnorm_vec      : %8.2f ns/call  %7.1f M ops/s  sink=%lld\n",
           best * 1e9 / N, N / best / 1e6, (long long)acc);
}

/* Invariant bench: same chord every iteration; volatile reload
 * defeats CSE. In debug builds this includes the assert. */
static void bench_invariant(void) {
    int64_t acc = 0;
    double best = 1e9;
    for (int rep = 0; rep < REPS; rep++) {
        acc = 0;
        double t0 = now_seconds();
        for (int i = 0; i < N; i++) {
            vec3 v = volatile_src;
            zphi r = invariant_rollover(v);
            acc += r.a + r.b;
        }
        double t1 = now_seconds();
        double e = t1 - t0;
        if (e < best) best = e;
    }
    printf("invariant_rollover    : %8.2f ns/call  %7.1f M ops/s  sink=%lld\n",
           best * 1e9 / N, N / best / 1e6, (long long)acc);
}

int main(void) {
    vec3 base = { {-1,0}, {-2,0}, {-1,-1} };
    volatile_src = base;

    printf("bench: N=%d, reps=%d (best-of-%d)\n\n", N, REPS, REPS);
    bench_primitive();
    bench_invariant();
    return 0;
}
