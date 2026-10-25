/* bench.c — measure the compass engine */
#define _POSIX_C_SOURCE 199309L  /* Required for clock_gettime under -std=c11 */

#include "ulda.h"
#include <stdio.h>
#include <time.h>
#include <stdint.h>

#define N 10000000

static double now_seconds(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (double)ts.tv_sec + (double)ts.tv_nsec * 1e-9;
}

int main(void) {
    /* The roll-over chord: O = (0, 1, φ) to Q = (−1, −1, −1) */
    vec3 v = { {-1,0}, {-2,0}, {-1,-1} };

    volatile int64_t sink = 0;

    /* Warm-up (not measured) */
    for (int i = 0; i < 1000; i++) {
        zphi r = chord_sqnorm_vec(v);
        sink += r.a + r.b;
    }

    /* The actual benchmark */
    double t0 = now_seconds();
    for (int i = 0; i < N; i++) {
        zphi r = chord_sqnorm_vec(v);
        sink += r.a + r.b;
    }
    double t1 = now_seconds();

    double elapsed = t1 - t0;
    double per_call_ns = elapsed * 1e9 / N;

    printf("chord_sqnorm_vec: %d iterations\n", N);
    printf("  total      : %.3f s\n", elapsed);
    printf("  per call   : %.2f ns\n", per_call_ns);
    printf("  ~cycles    : %.1f  (at 3 GHz)\n", per_call_ns * 3.0);
    printf("  throughput : %.1f M ops/s\n", N / elapsed / 1e6);
    printf("  sink       : %lld\n", (long long)sink);

    return 0;
}
