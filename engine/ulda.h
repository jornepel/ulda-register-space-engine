/* ulda.h — ULDA Topological Decoder Engine (new math) */
#ifndef ULDA_H
#define ULDA_H

#include <stdint.h>
#include <stddef.h>

/* ---------------------------------------------------------------
 * Rank 0 — labels (base-60, fixed width)
 * --------------------------------------------------------------- */

typedef struct {
    uint8_t axis;      /* 1..6 */
    int8_t  position;  /* +1 or -1 */
    uint8_t turn;      /* 1 or 2 */
    uint8_t base60;    /* 0, 12, 24, 36, 48 */
} label;

/* ---------------------------------------------------------------
 * Rank 1 — ℤ[φ] vectors (exact, no roots)
 * a + bφ, with φ² = φ + 1
 * --------------------------------------------------------------- */

typedef struct { int64_t a, b; } zphi;       /* a + bφ */
typedef struct { zphi x, y, z; } vec3;       /* ℤ[φ]³ */

/* ---------------------------------------------------------------
 * Rank 2 — readings (never computed)
 * --------------------------------------------------------------- */

typedef enum { METRIC, STRUCTURAL } invariant_type;

typedef struct {
    invariant_type type;
    zphi    sq_norm;   /* metric: squared norm in ℤ[φ] */
    int64_t count;     /* structural: integer invariant */
} invariant;

/* ---------------------------------------------------------------
 * ℤ[φ] arithmetic (exact)
 * --------------------------------------------------------------- */

static inline zphi zphi_make(int64_t a, int64_t b) { return (zphi){a, b}; }
static inline zphi zphi_add(zphi u, zphi v) { return (zphi){u.a+v.a, u.b+v.b}; }
static inline zphi zphi_sub(zphi u, zphi v) { return (zphi){u.a-v.a, u.b-v.b}; }

static inline zphi zphi_mul(zphi u, zphi v) {
    /* (a+bφ)(c+dφ) = ac + (ad+bc)φ + bdφ²
     *              = ac + (ad+bc)φ + bd(φ+1)
     *              = (ac+bd) + (ad+bc+bd)φ */
    int64_t ac = u.a * v.a;
    int64_t bd = u.b * v.b;
    int64_t ad = u.a * v.b;
    int64_t bc = u.b * v.a;
    return (zphi){ ac + bd, ad + bc + bd };
}

/* ---------------------------------------------------------------
 * Vector operations
 * --------------------------------------------------------------- */

static inline vec3 vec3_sub(vec3 u, vec3 v) {
    return (vec3){ zphi_sub(u.x, v.x), zphi_sub(u.y, v.y), zphi_sub(u.z, v.z) };
}

static inline zphi vec3_dot(vec3 u, vec3 v) {
    return zphi_add(zphi_add(zphi_mul(u.x, v.x),
                             zphi_mul(u.y, v.y)),
                    zphi_mul(u.z, v.z));
}

static inline zphi vec3_sqnorm(vec3 v) { return vec3_dot(v, v); }

/* ---------------------------------------------------------------
 * The engine — the four operations the paper actually uses
 * --------------------------------------------------------------- */

zphi chord_sqnorm(vec3 O, vec3 Q);
zphi invariant_rollover(vec3 O, vec3 Q);
zphi invariant_mirror(vec3 O, vec3 Q);
int64_t invariant_offset(void);
int64_t invariant_loop(void);

/* pretty-print helpers */
void zphi_print(zphi v, char *buf, size_t size);
void vec3_print(vec3 v, char *buf, size_t size);

#endif /* ULDA_H */
