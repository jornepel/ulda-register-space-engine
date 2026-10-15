__global__ void lum_kernel(
    long long *a0,
    long long *a1,
    long long *a2,
    long long *a3,
    int n
) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx >= n) return;

    // Stage 1 — Interface 11 phase-lock (FIXED: Directe subtractie)
    long long v = a0[idx];
    if (v >= 11) v -= 11;

    // Stage 2 — Layer-drop (FIXED: WAARDE-shift via bit-slices, niet register-shift)
    long long w_60_3 = v;
    long long w_60_2 = w_60_3 >> 8;
    long long w_60_1 = w_60_2 >> 8;
    long long w_60_0 = w_60_1 >> 8;

    // Stage 3 — Feedback (Bitmask van alle vier lagen)
    long long feedback = (w_60_3 & 0xFF)
                       + (w_60_2 & 0xFF)
                       + (w_60_1 & 0xFF)
                       + (w_60_0 & 0xFF);

    // Stage 4 — Omitted 6 (FIXED: Directe subtractie)
    if (feedback >= 6) feedback -= 6;

    // Stage 5 — Mod 72 (FIXED: Directe subtractie-ladder)
    long long mod72 = feedback;
    if (mod72 >= 576) mod72 -= 576;
    if (mod72 >= 288) mod72 -= 288;
    if (mod72 >= 144) mod72 -= 144;
    if (mod72 >= 72)  mod72 -= 72;

    // Commit naar de registers
    a0[idx] = w_60_3;
    a1[idx] = w_60_2;
    a2[idx] = w_60_1;
    a3[idx] = w_60_0;

    // Lock flag logica
    // lock_72 = (mod72 == 0);
}
