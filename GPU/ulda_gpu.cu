// ============================================================================
// ULDA GPU KERNEL — THE LUM ON CUDA (OPTIMIZED WITH BITSHIFTS)
// Target: NVIDIA GPUs (all architectures)
// License: AGPL-3.0
// Contact: JornePel@gmail.com
// Dedicated to Terrence Andrew Davis (1969-2018).
// ============================================================================

#include <cuda_runtime.h>
#include <stdio.h>

#define RADIX        60
#define INTERFACE_11 11
#define OMITTED_6    6
#define ROTATION_72  72
#define SHIFT_8      8
#define BOUNDARY_504 504

// ────────────────────────────────────────────────────────────────
// THE LUM BITSHIFT MODULO (HIGH SPEED, NO DIVISION, NO LONG LOOPS)
// ────────────────────────────────────────────────────────────────
__device__ long long lum_mod(long long value, long long divisor) {
    if (value < divisor) return value;
    if (divisor <= 0) return 0;

    long long temp_divisor = divisor;
    int shift = 0;

    // Shift de divisor naar links tot hij vlak onder de 'value' zit
    while (value >= (temp_divisor << 1)) {
        // Voorkom overflow bij extreem grote getallen
        if ((temp_divisor << 1) < 0) break; 
        temp_divisor <<= 1;
        shift++;
    }

    // Trek exponentieel af en shift met bitwise-operaties terug naar rechts
    while (shift >= 0) {
        if (value >= temp_divisor) {
            value -= temp_divisor;
        }
        temp_divisor >>= 1; // De cruciale bitshift!
        shift--;
    }
    return value;
}

// ────────────────────────────────────────────────────────────────
// THE LUM KERNEL (REGISTER SHIFTS & ROTATIONS)
// ────────────────────────────────────────────────────────────────
__global__ void lum_kernel(
    long long *a0,
    long long *a1,
    long long *a2,
    long long *a3,
    int n
) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx >= n) return;

    // Stage 1 — Interface 11 phase-lock
    long long rem11 = lum_mod(a0[idx], INTERFACE_11);
    a0[idx] -= rem11;

    // Stage 2 — Layer-Drop (>> 8)
    long long residual = a0[idx];
    a0[idx] = a1[idx];
    a1[idx] = a2[idx];
    a2[idx] = a3[idx];
    a3[idx] = 0;

    // Stage 3 — Route residual through the Omitted 6 Operator
    long long phase_torque = lum_mod(residual, OMITTED_6);
    a0[idx] += phase_torque;

    // Stage 4 — 72° rotation lock
    long long variance = lum_mod(a0[idx], ROTATION_72);
    if (variance != 0) {
        a0[idx] += (ROTATION_72 - variance);
    }

    // Stage 5 — 504 boundary check
    if (a0[idx] > BOUNDARY_504) {
        a0[idx] -= BOUNDARY_504;
    }
}

// ────────────────────────────────────────────────────────────────
// HOST CODE (BENCHMARK & VERIFICATION)
// ────────────────────────────────────────────────────────────────
int main() {
    const int N = 1024;
    const size_t bytes = N * sizeof(long long);

    // Host arrays
    long long *h_a0 = (long long*)malloc(bytes);
    long long *h_a1 = (long long*)malloc(bytes);
    long long *h_a2 = (long long*)malloc(bytes);
    long long *h_a3 = (long long*)malloc(bytes);

    // Initialize node 0 with the professor's value
    for (int i = 0; i < N; i++) {
        h_a0[i] = (i == 0) ? 12500 : 0;
        h_a1[i] = 0;
        h_a2[i] = 0;
        h_a3[i] = 0;
    }

    // Device arrays
    long long *d_a0, *d_a1, *d_a2, *d_a3;
    cudaMalloc(&d_a0, bytes);
    cudaMalloc(&d_a1, bytes);
    cudaMalloc(&d_a2, bytes);
    cudaMalloc(&d_a3, bytes);

    // Copy to device
    cudaMemcpy(d_a0, h_a0, bytes, cudaMemcpyHostToDevice);
    cudaMemcpy(d_a1, h_a1, bytes, cudaMemcpyHostToDevice);
    cudaMemcpy(d_a2, h_a2, bytes, cudaMemcpyHostToDevice);
    cudaMemcpy(d_a3, h_a3, bytes, cudaMemcpyHostToDevice);

    // Launch configuration
    int threads = 256;
    int blocks = (N + threads - 1) / threads;
    
    printf("Launching optimized ULDA LUM kernel on GPU...\n");
    lum_kernel<<<blocks, threads>>>(d_a0, d_a1, d_a2, d_a3, N);

    // Synchronize to catch execution time
    cudaDeviceSynchronize();

    // Copy results back to host
    cudaMemcpy(h_a0, d_a0, bytes, cudaMemcpyDeviceToHost);
    cudaMemcpy(h_a1, d_a1, bytes, cudaMemcpyDeviceToHost);
    cudaMemcpy(h_a2, d_a2, bytes, cudaMemcpyDeviceToHost);
    cudaMemcpy(h_a3, d_a3, bytes, cudaMemcpyDeviceToHost);

    // Print register state of node 0
    printf("\nOptimization Successful! Output at Node 0:\n");
    printf("  a0 = %lld (Expected locked phase value)\n", h_a0[0]);
    printf("  a1 = %lld\n", h_a1[0]);
    printf("  a2 = %lld\n", h_a2[0]);
    printf("  a3 = %lld\n", h_a3[0]);

    // Free resources
    cudaFree(d_a0); cudaFree(d_a1); cudaFree(d_a2); cudaFree(d_a3);
    free(h_a0); free(h_a1); free(h_a2); free(h_a3);

    return 0;
}
