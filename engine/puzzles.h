/* puzzles.h — the 12 puzzle assignments as data */
#ifndef PUZZLES_H
#define PUZZLES_H

#include "ulda.h"

typedef enum {
    READING_ROLLOVER,
    READING_MIRROR,
    READING_LOOP,
    READING_OFFSET
} reading_t;

typedef enum {
    MODE_ASSIGNED,
    MODE_UNASSIGNED
} mode_status_t;

typedef struct {
    const char   *name;
    label         observer;
    reading_t     reading;
    uint8_t       base60;      /* 0, 12, 24, 36, 48 */
    int           wave_mode;   /* 1, 3, 3', 4, 5 — encoded as int; -1 = unassigned */
    mode_status_t mode_status;
} puzzle;

/* The 12 puzzles (§7 of the paper). */
extern const puzzle PUZZLES[12];

/* The 20 dodecahedron vertices in ℤ[φ]³ (§6.2). */
extern const vec3 VERTICES[20];

/* The 12 observers (icosahedron vertices) in ℤ[φ]³ (§6.2). */
extern const vec3 OBSERVERS[12];

#endif /* PUZZLES_H */
