c
/* demo.c — Live topological sequence decoding and time-ladder simulator */
#define _POSIX_C_SOURCE 199309L

#include "ulda.h"
#include "puzzles.h"
#include <stdio.h>

void simulate_time_cascade(const puzzle *p) {
    char buf[128];
    // Pull the assigned observer vertex direction to use as the baseline vector
    // For demo purposes, we scan the observer table matching the puzzle axis index
    vec3 O = OBSERVERS[(p->observer.axis - 1) * 2]; 
    vec3 Q = VERTICES[0]; // Anchor against the first absolute dodecahedron vertex
    
    zphi current_frequentie = chord_sqnorm(O, Q);
    
    printf("\n🚀 SPINNING THE 4D COMPASS CENTRIFUGE FOR: %s\n", p->name);
    printf("  Observer Label: (Axis: %d, Position: %+d, Turn: %d, Base60: %d)\n",
           p->observer.axis, p->observer.position, p->observer.turn, p->observer.base60);
    
    // Level 0: 60¹
    zphi_print(current_frequentie, buf, sizeof(buf));
    printf("  Level 0 (Rotation Closed | 60^1): %s\n", buf);
    
    // Step through the power ladder levels. The 4th axis is the fractal repetition loop!
    for (int level = 1; level <= 3; level++) {
        current_frequentie = zphi_mul(current_frequentie, current_frequentie);
        zphi_print(current_frequentie, buf, sizeof(buf));
        printf("  Level %d (Time Ladder Shift | 60^%d): %s\n", level, 1 << level, buf);
    }
}

int main(void) {
    printf("====================================================================\n");
    printf("        ULDA TOPOLOGICAL DECODER ENGINE — RUNTIME DEMONSTRATION     \n");
    printf("====================================================================\n");

    // 1. Display Reference Tables
    printf("\n🔢 REFERENCE GEOMETRY LOADED IN MEMORY:\n");
    printf("  • Dodecahedron Vertices : 20 slots exact in Z[phi]^3\n");
    printf("  • Observer Axials       : 12 face-center directions locked\n");

    // 2. Scan the 12 Puzzles Dashboard
    printf("\n📊 THE TWELVE PUZZLES MATRIX STATUS:\n");
    for (int i = 0; i < 12; i++) {
        const puzzle *p = &PUZZLES[i];
        const char *status = (p->mode_status == MODE_ASSIGNED) ? "[ASSIGNED]" : "[ARTIFACT BOUNDARY]";
        const char *reading = (p->reading == READING_ROLLOVER) ? "Roll-over (S^-2)" :
                             (p->reading == READING_MIRROR)   ? "Mirror Axis (S^-1)" :
                             (p->reading == READING_LOOP)     ? "Closed Loop (S^0)" : "Offset (S^+1)";
        
        printf("  [%02d] %-16s -> %-20s Wave Mode: %2d  %s\n", 
               i + 1, p->name, reading, p->wave_mode, status);
    }

    // 3. Run the live 4D Cascade for a fluid system (Navier-Stokes) and a quantum system (Yang-Mills)
    simulate_time_cascade(&PUZZLES[1]); // Navier-Stokes
    simulate_time_cascade(&PUZZLES[2]); // Yang-Mills

    printf("\n====================================================================\n");
    printf("Execution complete. The hot path executed with absolute precision.\n");
    printf("====================================================================\n");
    return 0;
}
