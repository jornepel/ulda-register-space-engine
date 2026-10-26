/* puzzles.h — the 12 puzzle assignments as data */
#ifndef PUZZLES_H
#define PUZZLES_H

#include <stdint.h>
#include "ulda.h"

/* Which invariant of §8 this puzzle reads out. */
typedef enum {
    READING_ROLLOVER = 0,   /* METRIC,     expects 7 + 3φ */
    READING_MIRROR   = 1,   /* METRIC,     expects 3 + φ   */
    READING_LOOP     = 2,   /* STRUCTURAL, expects 5       */
    READING_OFFSET   = 3    /* STRUCTURAL, expects 1       */
} reading_t;

/* Map a reading to its invariant type (one place, no drift). */
static inline invariant_type reading_type(reading_t r) {
    return (r == READING_LOOP || r == READING_OFFSET) ? STRUCTURAL : METRIC;
}

/* Wave mode. WAVE_3P (3') is distinct from WAVE_3 (3) — do not
 * compare numerically. WAVE_UNASSIGNED is the single "not yet set"
 * sentinel; there is no separate mode_status field. */
typedef enum {
    WAVE_UNASSIGNED = 0,
    WAVE_1,
    WAVE_3,
    WAVE_3P,
    WAVE_4,
    WAVE_5
} wave_t;

typedef struct {
    const char *const name;
    label             observer;
    reading_t         reading;
    wave_t            wave;      /* WAVE_UNASSIGNED when not assigned */
} puzzle;

/* The 12 puzzles (§7 of the paper). */
extern const puzzle PUZZLES[12];

/* The 20 dodecahedron vertices in ℤ[φ]³ (§6.2).
 * Canonical projective reps (rule: <fill in>). */
extern const vec3 VERTICES[20];

/* The 12 observers (icosahedron vertices) in ℤ[φ]³ (§6.2).
 * Canonical projective reps (rule: <fill in>). */
extern const vec3 OBSERVERS[12];

#endif /* PUZZLES_H */
