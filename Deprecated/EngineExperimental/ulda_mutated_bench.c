/* ========================================================================
 * ulda_mutated_bench.c — Forced Runtime Mutation Benchmark
 * Forces active CPU calculation by defeating compile-time constant folding.
 * ======================================================================== */
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

int main(void) {
    /* Initialize the standard antipodal chord base */
    vec3 base = { {0,0}, {1,0}, {0,1} };
    int64_t acc = 0;
    double best = 1e9;

    /* The Volatile Mutation Variable: forces runtime calculation loops */
    volatile int mutation_trigger = 0;

    printf("Executing Forced Runtime Mutation Bench: N=%d (Best-of-%d)\n", N, REPS);
    printf("--------------------------------------------------------------------\n");

    for (int rep = 0; rep < REPS; rep++) {
        acc = 0;
        double t0 = now_seconds();
        
        for (int i = 0; i < N; i++) {
            vec3 v = base;
            
            /* Inject the live runtime mutation directly into the X coordinate.
             * The volatile read forces the compiler to re-run the vector logic 
             * and execute vec3_sqnorm natively on every single loop iteration. */
            v.x.a += (mutation_trigger & 1);
            
            zphi r = chord_sqnorm_vec(v);
            acc += r.a + r.b;
            
            /* Mutate the variable on every loop pass */
            mutation_trigger = i;
        }
        
        double t1 = now_seconds();
        double e = t1 - t0;
        if (e < best) best = e;
    }

    printf("Forced Runtime Primitive Performance:\n");
    printf("  Execution Latency : %8.2f ns/call\n", best * 1e9 / N);
    printf("  Silicon Throughput: %7.1f M ops/s\n", N / best / 1e6);
    printf("  Data Sink Output  : %lld\n", (long long)acc);
    printf("--------------------------------------------------------------------\n");
    return 0;
}
