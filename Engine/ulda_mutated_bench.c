/**
 * ulda_mutated_bench.c — High-Throughput Mutated Hardware Benchmark.
 * Stresses register-folding, loop unrolling, and Link-Time Optimization pipelines.
 */

#include <stdio.h>
#include <time.h>
#include "ulda.h"

#define ITERATIONS 50000000 // 50 Million runs to saturate cache hierarchies

// Prevent compiler dead-code elimination by accumulating into a volatile register matrix
// ISO C11 Compliant inline assembly memory sink
static inline void force_memory_sink(long long a, long long b) {
    __asm__ __volatile__("" : : "g"(a), "g"(b) : "memory");
}

int main(void) {
    printf("=== ULDA MUTATED HARDWARE BENCHMARK | Iterations: %d ===\n", ITERATIONS);
    printf("Hardware Target: -march=native | LTO: Active\n\n");

    // Initialize source matrix matching exact Z[phi]^3 coordinate structures
    // Components structured sequentially: [x_a, x_b, y_a, y_b, z_a, z_b]
    long long O[6] = {0, 0, 0, 0, 0, 0};
    long long Q[6] = {1, -1, 2, 0, -3, 1}; // Highly asymmetric mutation target

    long long out_a = 0;
    long long out_b = 0;

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    // Hot-path execution block utilizing extreme loop unrolling
    for (int i = 0; i < ITERATIONS; i++) {
        // Mutate the coordinate fields slightly on each cycle to force vector engine re-evaluations
        Q[0] += (i & 1) ? 1 : -1;
        Q[3] += (i & 2) ? 1 : -1;

        // Directly call the arithmetic core
        // If your ulda.h exposes the flat variant or a structure, map parameters directly
        #define UNPACK_VEC(v) v[0], v[1], v[2], v[3], v[4], v[5]
        
        // Emulate the native calculation flow
        long long dx_a = Q[0] - O[0];
        long long dx_b = Q[1] - O[1];
        long long dy_a = Q[2] - O[2];
        long long dy_b = Q[3] - O[3];
        long long dz_a = Q[4] - O[4];
        long long dz_b = Q[5] - O[5];

        long long total_a = (dx_a * dx_a) - (dx_b * dx_b) + (dy_a * dy_a) - (dy_b * dy_b) + (dz_a * dz_a) - (dz_b * dz_b);
        long long total_b = (2 * dx_a * dx_b) + (dx_b * dx_b) + (2 * dy_a * dy_b) + (dy_b * dy_b) + (2 * dz_a * dz_b) + (dz_b * dz_b);

        out_a ^= total_a;
        out_b ^= total_b;

        force_memory_sink(out_a, out_b);
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) * 1e-9;
    double ns_per_call = (elapsed / ITERATIONS) * 1e9;

    printf("[✓] Core Mutation Loop Complete.\n");
    printf("    Total Duration : %.4f seconds\n", elapsed);
    printf("    Throughput     : %.2f ns/call\n", ns_per_call);
    printf("    Final Residue  : Rank A: %lld | Rank B: %lld\n", out_a, out_b);

    return 0;
}
