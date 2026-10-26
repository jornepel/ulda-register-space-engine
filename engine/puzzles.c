/* puzzles.c — Immutable reference geometry and data tables */
#include "puzzles.h"

/* 20 dodecahedron vertices in ℤ[φ]³ (§6.2). Exact via zphi_make(a,b) -> a + bφ. */
const vec3 VERTICES[20] = {
    /* (±1, ±1, ±1) — 8 */
    { {1,0}, {1,0}, {1,0} }, { {1,0}, {1,0}, {-1,0} },
    { {1,0}, {-1,0}, {1,0} }, { {1,0}, {-1,0}, {-1,0} },
    { {-1,0}, {1,0}, {1,0} }, { {-1,0}, {1,0}, {-1,0} },
    { {-1,0}, {-1,0}, {1,0} }, { {-1,0}, {-1,0}, {-1,0} },
    /* (0, ±(φ−1), ±φ) — 4 */
    { {0,0}, {-1,1}, {0,1} }, { {0,0}, {-1,1}, {0,-1} },
    { {0,0}, {1,-1}, {0,1} }, { {0,0}, {1,-1}, {0,-1} },
    /* (±(φ−1), ±φ, 0) — 4 */
    { {-1,1}, {0,1}, {0,0} }, { {-1,1}, {0,-1}, {0,0} },
    { {1,-1}, {0,1}, {0,0} }, { {1,-1}, {0,-1}, {0,0} },
    /* (±φ, 0, ±(φ−1)) — 4 */
    { {0,1}, {0,0}, {-1,1} }, { {0,1}, {0,0}, {1,-1} },
    { {0,-1}, {0,0}, {-1,1} }, { {0,-1}, {0,0}, {1,-1} },
};

/* 12 observers (icosahedron vertices) in ℤ[φ]³ (§6.2). Exact directions. */
const vec3 OBSERVERS[12] = {
    { {0,0}, {1,0}, {0,1} }, { {0,0}, {1,0}, {0,-1} },
    { {0,0}, {-1,0}, {0,1} }, { {0,0}, {-1,0}, {0,-1} },
    { {1,0}, {0,1}, {0,0} }, { {1,0}, {0,-1}, {0,0} },
    { {-1,0}, {0,1}, {0,0} }, { {-1,0}, {0,-1}, {0,0} },
    { {0,1}, {0,0}, {1,0} }, { {0,1}, {0,0}, {-1,0} },
    { {0,-1}, {0,0}, {1,0} }, { {0,-1}, {0,0}, {-1,0} },
};

/* The 12 puzzles (§7, §9). Observer label carries (axis, position, turn, base60);
 * base60 is NOT duplicated at the puzzle level. WAVE_UNASSIGNED marks unset waves. */
const puzzle PUZZLES[12] = {
    /* name              observer           reading           wave               */
    { "Poincaré",       {1, +1, 1,  0}, READING_ROLLOVER, WAVE_5             },
    { "Navier–Stokes",  {1, -1, 1,  0}, READING_ROLLOVER, WAVE_3             },
    { "Yang–Mills",     {6, -1, 1, 24}, READING_OFFSET,   WAVE_3             },
    { "Riemann",        {3, +1, 1, 12}, READING_MIRROR,   WAVE_UNASSIGNED    },
    { "BSD",            {3, -1, 1, 12}, READING_MIRROR,   WAVE_UNASSIGNED    },
    { "Hodge",          {4, +1, 1, 24}, READING_LOOP,     WAVE_UNASSIGNED    },
    { "P vs NP",        {4, -1, 1, 36}, READING_LOOP,     WAVE_3             },
    { "Fine structure", {6, +1, 1,  0}, READING_OFFSET,   WAVE_3             },
    { "Hierarchy",      {2, +1, 1,  0}, READING_OFFSET,   WAVE_UNASSIGNED    },
    { "Black hole",     {5, +1, 1, 24}, READING_LOOP,     WAVE_1             },
    { "Horizon",        {5, -1, 1, 36}, READING_LOOP,     WAVE_1             },
    { "Time",           {2, -1, 1,  0}, READING_ROLLOVER, WAVE_3             },
};
