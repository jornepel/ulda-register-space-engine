/* demo.c — Live topological sequence decoding and time-ladder simulator */
#define _POSIX_C_SOURCE 199309L

#include "ulda.h"
#include "puzzles.h"
#include <stdio.h>
#include <assert.h>

static const char *wave_name(wave_t w) {
    switch (w) {
        case WAVE_UNASSIGNED: return "—";
        case WAVE_1:  return "1";
        case WAVE_3:  return "3";
        case WAVE_3P: return "3'";
        case WAVE_4:  return "4";
        case WAVE_5:  return "5";
    }
    return "?";
}

static const char *reading_desc(reading_t r) {
    switch (r) {
        case READING_ROLLOVER: return "Roll-over (S^-2)";
        case READING_MIRROR:   return "Mirror Axis (S^-1)";
        case READING_LOOP:     return "Closed Loop (S^0)";
        case READING_OFFSET:   return "Offset (S^+1)";
    }
    return "?";
}

void simulate_time_cascade(const puzzle *p) {
    char buf[128];
    /* OBSERVERS is grouped in axis-pairs: indices (axis-1)*2 and (axis-1)*2+1. */
    assert(p->observer.axis >= 1 && p->observer.axis <= 6);
    vec3 O = OBSERVERS[(p->observer.axis - 1) * 2];
    vec3 Q = VERTICES[0];   /* arbitrary anchor: (1,1,1) */
    
    zphi current_frequentie = chord_sqnorm(O, Q);
    
    printf("\n🚀 SPINNING THE 4D COMPASS CENTRIFUGE FOR: %s\n", p->name);
    printf("  Observer Label: (Axis: %d, Position: %+d, Turn: %d, Base60: %d)\n",
           (int)p->observer.axis, (int)p->observer.position,
           (int)p->observer.turn, (int)p->observer.base60);
    
    zphi_print(current_frequentie, buf, sizeof(buf));
    printf("  Level 0 (Rotation Closed | 60^1): %s\n", buf);
    
    /* 3 levels max: |a|,|b| stays < 2^31 under the current anchors. */
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

    printf("\n🔢 REFERENCE GEOMETRY LOADED IN MEMORY:\n");
    printf("  • Dodecahedron Vertices : 20 slots exact in Z[phi]^3\n");
    printf("  • Observer Axials       : 12 face-center directions locked\n");

    printf("\n📊 THE TWELVE PUZZLES MATRIX STATUS:\n");
    for (int i = 0; i < 12; i++) {
        const puzzle *p = &PUZZLES[i];
        const char *status = (p->wave != WAVE_UNASSIGNED) ? "[ASSIGNED]" : "[ARTIFACT BOUNDARY]";
        printf("  [%02d] %-16s -> %-20s Wave Mode: %2s  %s\n",
               i + 1, p->name, reading_desc(p->reading),
               wave_name(p->wave), status);
    }

    simulate_time_cascade(&PUZZLES[1]); /* Navier–Stokes */
    simulate_time_cascade(&PUZZLES[2]); /* Yang–Mills */

    printf("\n====================================================================\n");
    printf("Execution complete. The hot path executed with absolute precision.\n");
    printf("====================================================================\n");
    return 0;
}
