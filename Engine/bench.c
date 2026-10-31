/* ============================================================================
 * bench.c — High-Performance Loop-Unrolled Throughput Benchmark
 * Measures raw zphi_mul ring multiplication speeds down to the nanosecond.
 * ============================================================================
 */

#include "ulda_unified.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define ITERATIONS 100000000

int main(void) {
    LARGE_INTEGER frequency;
    LARGE_INTEGER start_time;
    LARGE_INTEGER end_time;

    QueryPerformanceFrequency(&frequency);

    printf("====================================================================\n");
    printf(" INITIALIZING HIGH-PERFORMANCE NANO-BENCHMARK FOR zphi_mul         \n");
    printf(" Total Execution Iterations: %d\n", ITERATIONS);
    printf("====================================================================\n\n");

    /* Initialize mock coordinate registers to stress the hot path */
    zphi n1 = {123456, 789012};
    zphi n2 = {654321, 210987};
    zphi dummy_accumulator = {0, 0};

    printf("[ STATUS ] Running unrolled multiplication execution loops...\n");
    QueryPerformanceCounter(&start_time);

    /* Unrolled by 8 to maximize instruction pipeline saturation inside the CPU */
    for (uint32_t i = 0; i < ITERATIONS; i += 8) {
        dummy_accumulator = zphi_mul(n1, n2);
        dummy_accumulator = zphi_mul(dummy_accumulator, n1);
        dummy_accumulator = zphi_mul(dummy_accumulator, n2);
        dummy_accumulator = zphi_mul(dummy_accumulator, n1);
        
        dummy_accumulator = zphi_mul(dummy_accumulator, n2);
        dummy_accumulator = zphi_mul(dummy_accumulator, n1);
        dummy_accumulator = zphi_mul(dummy_accumulator, n2);
        dummy_accumulator = zphi_mul(dummy_accumulator, n1);
    }

    QueryPerformanceCounter(&end_time);

    /* Computational metrics transformation pass */
    double total_time_seconds = (double)(end_time.QuadPart - start_time.QuadPart) / (double)frequency.QuadPart;
    double nanoseconds_per_call = (total_time_seconds * 1e9) / (double)ITERATIONS;

    printf("\n====================================================================\n");
    printf(" BENCHMARK PROFILING RESULTS COMPLETE                               \n");
    printf("====================================================================\n");
    printf(" Total Elapsed Runtime : %f seconds\n", total_time_seconds);
    printf(" Hardware Throughput   : %f ns per zphi_mul call\n", nanoseconds_per_call);
    printf(" Checksum Accumulator  : (%lld + %lldφ)\n", (long long)dummy_accumulator.a, (long long)dummy_accumulator.b);
    printf("====================================================================\n");

    return 0;
}
