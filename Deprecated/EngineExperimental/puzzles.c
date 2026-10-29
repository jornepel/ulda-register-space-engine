/* ========================================================================
 * puzzles.c — Exact Coordinate Definitions for ULDA Grid Engine
 * ======================================================================== */
#include "puzzles.h"

/* The 20 Dodecahedron vertices in ℤ[φ]³ (§6.2) */
const vec3 VERTICES[20] = {
    /* Standard Cube Group: (±1, ±1, ±1) */
    {{ 1, 0}, { 1, 0}, { 1, 0}},  {{ 1, 0}, { 1, 0}, {-1, 0}},
    {{ 1, 0}, {-1, 0}, { 1, 0}},  {{ 1, 0}, {-1, 0}, {-1, 0}},
    {{-1, 0}, { 1, 0}, { 1, 0}},  {{-1, 0}, { 1, 0}, {-1, 0}},
    {{-1, 0}, {-1, 0}, { 1, 0}},  {{-1, 0}, {-1, 0}, {-1, 0}},

    /* Golden Scaling Group: (0, ±(φ-1), ±φ) and cyclic permutations */
    {{ 0, 0}, {-1, 1}, { 0, 1}},  {{ 0, 0}, {-1, 1}, { 0,-1}},
    {{ 0, 0}, { 1,-1}, { 0, 1}},  {{ 0, 0}, { 1,-1}, { 0,-1}},

    {{ 0, 1}, { 0, 0}, {-1, 1}},  {{ 0, 1}, { 0, 0}, { 1,-1}},
    {{ 0,-1}, { 0, 0}, {-1, 1}},  {{ 0,-1}, { 0, 0}, { 1,-1}},

    {{-1, 1}, { 0, 1}, { 0, 0}},  {{-1, 1}, { 0,-1}, { 0, 0}},
    {{ 1,-1}, { 0, 1}, { 0, 0}},  {{ 1,-1}, { 0,-1}, { 0, 0}}
};

/* The 12 Observers (Icosahedron vertices) in ℤ[φ]³ (§6.2) */
const vec3 OBSERVERS[12] = {
    {{ 0, 0}, { 1, 0}, { 0, 1}},  {{ 0, 0}, { 1, 0}, { 0,-1}},
    {{ 0, 0}, {-1, 0}, { 0, 1}},  {{ 0, 0}, {-1, 0}, { 0,-1}},

    {{ 0, 1}, { 0, 0}, { 1, 0}},  {{ 0, 1}, { 0, 0}, {-1, 0}},
    {{ 0,-1}, { 0, 0}, { 1, 0}},  {{ 0,-1}, { 0, 0}, {-1, 0}},

    {{ 1, 0}, { 0, 1}, { 0, 0}},  {{ 1, 0}, { 0,-1}, { 0, 0}},
    {{-1, 0}, { 0, 1}, { 0, 0}},  {{-1, 0}, { 0,-1}, { 0, 0}}
};

/* Exemplar definition of the 12 cosmic puzzles mapped to sections */
const puzzle PUZZLES[12] = {
    {"Theme_1_Aether",   {1,  1, 1,  0}, READING_ROLLOVER, WAVE_5},
    {"Theme_2_Discord",  {2, -1, 1, 12}, READING_MIRROR,   WAVE_3},
    {"Theme_3_Flame",    {3, -1, 2, 24}, READING_LOOP,     WAVE_3P},
    {"Theme_4_Manwe",    {4,  1, 1, 36}, READING_OFFSET,   WAVE_1},
    {"Theme_5_Ulmo",     {5, -1, 1, 48}, READING_MIRROR,   WAVE_4},
    {"Theme_6_Aule",     {6,  1, 2,  0}, READING_ROLLOVER, WAVE_5},
    {"Theme_7_Mandos",   {1, -1, 1, 12}, READING_LOOP,     WAVE_3},
    {"Theme_8_Varda",    {2,  1, 2, 24}, READING_OFFSET,   WAVE_1},
    {"Theme_9_Orome",    {3,  1, 1, 36}, READING_MIRROR,   WAVE_4},
    {"Theme_10_Yavanna", {4, -1, 2, 48}, READING_LOOP,     WAVE_3P},
    {"Theme_11_Nienna",  {5,  1, 1,  0}, READING_OFFSET,   WAVE_1},
    {"Theme_12_Melkor",  {6, -1, 2, 12}, READING_ROLLOVER, WAVE_5}
};
