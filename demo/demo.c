/* demo.c — demonstrate the compass */
#include "ulda.h"
#include "puzzles.h"
#include <stdio.h>
#include <string.h>

/* The four invariants, by name. */
static const char *invariant_name(reading_t r) {
    switch (r) {
        case READING_ROLLOVER: return "roll-over";
        case READING_MIRROR:   return "mirror axis";
        case READING_LOOP:     return "closed loop";
        case READING_OFFSET:   return "offset";
    }
    return "?";
}

/* The invariant value, as a string, for the reading. */
static void invariant_value(reading_t r, char *buf, size_t size) {
    switch (r) {
        case READING_ROLLOVER: {
            zphi v = zphi_make(7, 3);
            zphi_print(v, buf, size);
            break;
        }
        case READING_MIRROR: {
            zphi v = zphi_make(3, 1);
            zphi_print(v, buf, size);
            break;
        }
        case READING_LOOP:
            snprintf(buf, size, "order 5");
            break;
        case READING_OFFSET:
            snprintf(buf, size, "1 (edge)");
            break;
    }
}

int main(void) {
    printf("=== The Compass — Demonstration ===\n\n");

    /* 1. The 20 vertices. */
    printf("1. The 20 dodecahedron vertices (in Z[phi]^3):\n");
    for (int i = 0; i < 20; i++) {
        char buf[128];
        vec3_print(VERTICES[i], buf, sizeof buf);
        printf("   V%d: %s\n", i + 1, buf);
    }
    printf("   (20 vertices, exact in Z[phi]^3)\n\n");

    /* 2. The 12 observers. */
    printf("2. The 12 observers (icosahedron vertices, face centers):\n");
    for (int i = 0; i < 12; i++) {
        char buf[128];
        vec3_print(OBSERVERS[i], buf, sizeof buf);
        printf("   O%d: %s\n", i + 1, buf);
    }
    printf("   (12 observers, exact in Z[phi]^3)\n\n");

    /* 3. The 240 chords and their squared norms. */
    printf("3. The 240 chords (12 observers x 20 vertices) and their squared norms:\n");
    int chord_count = 0;
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 20; j++) {
            vec3 v = vec3_sub(VERTICES[j], OBSERVERS[i]);
            zphi n = chord_sqnorm_vec(v);
            char buf[64];
            zphi_print(n, buf, sizeof buf);
            chord_count++;
        }
    }
    printf("   (240 chords computed, all exact in Z[phi])\n");
    printf("   (%d chords total)\n\n", chord_count);

    /* 4. The four invariants. */
    printf("4. The four invariants:\n");
    char buf[64];
    zphi v = zphi_make(7, 3);
    zphi_print(v, buf, sizeof buf);
    printf("   roll-over    : %s   (metric)\n", buf);
    v = zphi_make(3, 1);
    zphi_print(v, buf, sizeof buf);
    printf("   mirror axis  : %s   (metric)\n", buf);
    printf("   offset       : 1 (edge count)   (structural)\n");
    printf("   closed loop  : order 5   (structural)\n\n");

    /* 5. The 12 puzzles. */
    printf("5. The 12 puzzles:\n");
    for (int i = 0; i < 12; i++) {
        const puzzle *p = &PUZZLES[i];
        char inv_buf[64];
        invariant_value(p->reading, inv_buf, sizeof inv_buf);
        const char *status = (p->mode_status == MODE_ASSIGNED) ? "assigned" : "unassigned";
        printf("   %-16s  %-12s  invariant: %-12s  wave: %d  (%s)\n",
               p->name, invariant_name(p->reading), inv_buf, p->wave_mode, status);
    }
    printf("\n");

    /* 6. The scope boundary. */
    printf("6. The scope boundary:\n");
    printf("   Four puzzles are unassignable because the compass rounds\n");
    printf("   a general operation to a specific one:\n");
    printf("     Riemann    — locating    (1/2 -> Z[phi])\n");
    printf("     BSD        — counting    (variable rank -> 3)\n");
    printf("     Hodge      — looping     (rank 0 -> rank 1)\n");
    printf("     Hierarchy  — comparing   (ratio -> force)\n");
    printf("   The rounding is the artifact. The artifact is the boundary.\n\n");

    printf("=== End of demonstration ===\n");
    return 0;
}
