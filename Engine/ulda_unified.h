/* ============================================================================
 * ulda_unified.h - Unified Header for Z[phi]^3 Topological Engine Module
 * Bridges the unified translation unit to external modules and link boundaries.
 * ============================================================================
 */

#ifndef ULDA_UNIFIED_H
#define ULDA_UNIFIED_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Export macros for dynamic link library interfaces */
#if defined(_WIN32) || defined(_WIN64)
    #define EXPORT __declspec(dllexport)
#else
    #define EXPORT __attribute__((visibility("default")))
#endif

/* ----------------------------------------------------------------------------
 * 1. CORE TYPE DEFINITIONS
 * ----------------------------------------------------------------------------
 */
typedef struct {
    int64_t a;
    int64_t b;
} zphi;

typedef struct {
    zphi x;
    zphi y;
    zphi z;
} vec3;

typedef struct {
    zphi m00, m01, m02;
    zphi m10, m11, m12;
    zphi m20, m21, m22;
} mat3;

/* ----------------------------------------------------------------------------
 * 2. EXPORTED ENGINE ARITHMETIC & INVARIANTS
 * ----------------------------------------------------------------------------
 */
EXPORT int64_t invariant_offset(void);
EXPORT int64_t invariant_loop(void);

zphi zphi_add(zphi n1, zphi n2);
zphi zphi_mul(zphi n1, zphi n2);
vec3 mat3_mul_vec3(mat3 m, vec3 v);

int64_t chord_sqnorm(zphi n);
zphi    chord_sqnorm_vec(vec3 v);

EXPORT zphi invariant_rollover(vec3 v);
EXPORT zphi invariant_mirror(vec3 v);

/* ----------------------------------------------------------------------------
 * 3. EXPORTED FLAT MEMORY & ABI SHIM LAYER
 * ----------------------------------------------------------------------------
 */
EXPORT vec3* ulda_alloc_vector(int64_t xa, int64_t xb, int64_t ya, int64_t yb, int64_t za, int64_t zb);
EXPORT mat3* ulda_alloc_matrix(void);
EXPORT void  ulda_free_memory(void* ptr);

EXPORT void    ulda_shim_vec3_add(const vec3* v1, const vec3* v2, vec3* result_out);
EXPORT void    ulda_shim_mat3_transform(const mat3* m, const vec3* v, vec3* result_out);
EXPORT void    ulda_shim_get_sqnorm(const vec3* v, zphi* norm_out);
EXPORT int64_t ulda_shim_get_scalar_norm(int64_t a, int64_t b);
EXPORT int     ulda_shim_verify_horizon(const vec3* v, int check_type);

/* ----------------------------------------------------------------------------
 * 4. STRING EXPORT FORMATTERS
 * ----------------------------------------------------------------------------
 */
EXPORT void zphi_print(zphi v, char *buf, size_t size);
EXPORT void vec3_print(vec3 v, char *buf, size_t size);

#ifdef __cplusplus
}
#endif

#endif /* ULDA_UNIFIED_H */
