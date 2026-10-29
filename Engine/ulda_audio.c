/**
 * ulda_audio.c — Native C Topological Acoustic Wave Engine.
 * Bypasses high-level language wrappers to drive microtonal sound directly via hardware.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifdef _WIN32
    #include <windows.h> // Dynamic core hardware Beep API
#else
    #include <unistd.h>
    #define Sleep(ms) usleep((ms) * 1000)
#endif

#include "ulda.h"
#include "puzzles.h"

#define VECTOR_LANES 6
#define TORUS_COUNT 4
#define BASE_WHEEL 60.0

typedef long long i64;

typedef struct {
    i64 O[VECTOR_LANES];
    i64 Q[VECTOR_LANES];
    i64 seed_Q[VECTOR_LANES];
    int gear;
    int seed_gear;
    char sym;
    const char* label;
} AudioTorus;

// Link to the flat bridge implementation
void chord_sqnorm_flat(
    i64 Ox_a, i64 Ox_b, i64 Oy_a, i64 Oy_b, i64 Oz_a, i64 Oz_b,
    i64 Qx_a, i64 Qx_b, i64 Qy_a, i64 Qy_b, i64 Qz_a, i64 Qz_b,
    i64* out_a, i64* out_b
);

int main(void) {
    printf("====================================================================\n");
    printf("     ULDA NATIVE AUDIO: HARDWARE MICROTONAL STEP PROCESSOR          \n");
    printf("     Status: Streaming Frequencies directly to Windows Sound Core ✓ \n");
    printf("====================================================================\n\n");

    AudioTorus tracks[TORUS_COUNT] = {
        {{0,0,0,0,0,0}, {0, 0, -1, 1, 0, 1}, {0, 0, -1, 1, 0, 1}, 1, 1, 'A', "Riemann"},
        {{0,0,0,0,0,0}, {-1, 0, -1, 0, -1, 0}, {-1, 0, -1, 0, -1, 0}, -1, -1, 'B', "BSD"},
        {{0,0,0,0,0,0}, {0, 0, -1, 1, 0, 1}, {0, 0, -1, 1, 0, 1}, -1, -1, 'C', "Parallel Mirror"},
        {{0,0,0,0,0,0}, {-1, 0, -1, 0, -1, 0}, {-1, 0, -1, 0, -1, 0}, 1, 1, 'D', "Hierarchy"}
    };

    i64 out_a = 0, out_b = 0;
    int tick = 0;

    while (1) {
        double mixed_frequency = 0.0;

        for (int i = 0; i < TORUS_COUNT; i++) {
            AudioTorus* p = &tracks[i];

            // Drive mechanical axis steps
            p->Q[0] += p->gear;
            p->Q[3] += p->gear;

            // Compute exact metric norms
            chord_sqnorm_flat(
                p->O[0], p->O[1], p->O[2], p->O[3], p->O[4], p->O[5],
                p->Q[0], p->Q[1], p->Q[2], p->Q[3], p->Q[4], p->Q[5],
                &out_a, &out_b
            );

            // Invariant Snap Rules
            if (out_a == 3 && out_b == 1) p->gear *= -1;
            if (out_a == 7 && out_b == 3) {
                memcpy(p->Q, p->seed_Q, sizeof(p->Q));
                p->gear = p->seed_gear;
            }

            // Map current vector magnitude to microtonal audio frequency scale
            double freq_scale = BASE_WHEEL * (1.0 + (double)(llabs(p->Q[0]) % 12) / 12.0);
            mixed_frequency += freq_scale;
        }

        // Calculate master combined hardware pitch target
        int hardware_frequency = (int)(mixed_frequency / TORUS_COUNT) * 4; 
        if (hardware_frequency < 37) hardware_frequency = 37; // Keep within hardware limits

        printf("\033[H[Topological Audio Stream] Frame: %04d | Freq Target: %d Hz   \n", tick, hardware_frequency);
        fflush(stdout);

        #ifdef _WIN32
            // Fire the hardware tone natively for a duration of 80ms
            Beep((DWORD)hardware_frequency, 80); 
        #else
            Sleep(80);
        #endif

        tick++;
    }
    return 0;
}
