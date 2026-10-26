/* puzzles.c — Immutable reference geometry and data tables */
#include "puzzles.h"

/* 20 dodecahedron vertices in ℤ[φ]³ (§6.2). All exact via zphi_make(a, b) -> a + bφ */
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

/* 12 observers (icosahedron vertices) in ℤ[φ]³ (§6.2). Stored as exact directions. */
const vec3 OBSERVERS[12] = {
    { {0,0}, {1,0}, {0,1} }, { {0,0}, {1,0}, {0,-1} },
    { {0,0}, {-1,0}, {0,1} }, { {0,0}, {-1,0}, {0,-1} },
    { {1,0}, {0,1}, {0,0} }, { {1,0}, {0,-1}, {0,0} },
    { {-1,0}, {0,1}, {0,0} }, { {-1,0}, {0,-1}, {0,0} },
    { {0,1}, {0,0}, {1,0} }, { {0,1}, {0,0}, {-1,0} },
    { {0,-1}, {0,0}, {1,0} }, { {0,-1}, {0,0}, {-1,0} },
};

/* The 12 puzzles (§7, §9). Observers are tracked via (axis, position, turn, base60). */
const puzzle PUZZLES[12] = {
    { "Poincaré",       {1, +1, 1, 0},  READING_ROLLOVER, 0,  5, MODE_ASSIGNED   },
    { "Navier–Stokes",  {1, -1, 1, 0},  READING_ROLLOVER, 0,  3, MODE_ASSIGNED   },
    { "Yang–Mills",     {6, -1, 1, 24}, READING_OFFSET,   24, 3, MODE_ASSIGNED   },
    { "Riemann",        {3, +1, 1, 12}, READING_MIRROR,   12, -1, MODE_UNASSIGNED },
    { "BSD",            {3, -1, 1, 12}, READING_MIRROR,   12, -1, MODE_UNASSIGNED },
    { "Hodge",          {4, +1, 1, 24}, READING_LOOP,     24, -1, MODE_UNASSIGNED },
    { "P vs NP",        {4, -1, 1, 36}, READING_LOOP,     36, 3, MODE_ASSIGNED   },
    { "Fine structure", {6, +1, 1, 0},  READING_OFFSET,   0,  3, MODE_ASSIGNED   },
    { "Hierarchy",      {2, +1, 1, 0},  READING_OFFSET,   0, -1, MODE_UNASSIGNED },
    { "Black hole",     {5, +1, 1, 24}, READING_LOOP,     24, 1, MODE_ASSIGNED   },
    { "Horizon",        {5, -1, 1, 36}, READING_LOOP,     36, 1, MODE_ASSIGNED   },
    { "Time",           {2, -1, 1, 0},  READING_ROLLOVER, 0,  3, MODE_ASSIGNED   },
};
