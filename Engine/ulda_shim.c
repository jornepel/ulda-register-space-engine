/* ============================================================================
 * ulda_shim.c — Flat C Pointer Memory Interface & ABI Stabilization Wrapper
 * Exposes clean structural layouts to the dynamic linker boundary.
 * ============================================================================
 */

#include "ulda.h"
#include <stdlib.h>
#include <string.h>

#if defined(_WIN32) || defined(_WIN64)
    #define EXPORT __declspec(dllexport)
#else
    #define EXPORT __attribute__((visibility("default")))
#endif

/* ----------------------------------------------------------------------------
 * 1. MEMORY MANAGEMENT LIFECYCLES
 * ----------------------------------------------------------------------------
 */

EXPORT vec3* ulda_alloc_vector(int64_t xa, int64_t xb, int64_t ya, int64_t yb, int64_t za, int64_t zb) {
    vec3* v = (vec3*)malloc(sizeof(vec3));
    if (!v) return NULL;
    
    v->x.a = xa; v->x.b = xb;
    v->y.a = ya; v->y.b = yb;
    v->z.a = za; v->z.b = zb;
    
    return v;
}

EXPORT mat3* ulda_alloc_matrix(void) {
    mat3* m = (mat3*)malloc(sizeof(mat3));
    if (!m) return NULL;
    memset(m, 0, sizeof(mat3));
    return m;
}

EXPORT void ulda_free_memory(void* ptr) {
    if (ptr) {
        free(ptr);
    }
}

/* ----------------------------------------------------------------------------
 * 2. STRUCTURAL SHIM ARITHMETIC PASSTHROUGHS
 * ----------------------------------------------------------------------------
 */

EXPORT void ulda_shim_vec3_add(const vec3* v1, const vec3* v2, vec3* result_out) {
    if (!v1 || !v2 || !result_out) return;
    result_out->x = zphi_add(v1->x, v2->x);
    result_out->y = zphi_add(v1->y, v2->y);
    result_out->z = zphi_add(v1->z, v2->z);
}

EXPORT void ulda_shim_mat3_transform(const mat3* m, const vec3* v, vec3* result_out) {
    if (!m || !v || !result_out) return;
    *result_out = mat3_mul_vec3(*m, *v);
}

/* ----------------------------------------------------------------------------
 * 3. METRIC METADATA READBACKS
 * ----------------------------------------------------------------------------
 */

EXPORT void ulda_shim_get_sqnorm(const vec3* v, zphi* norm_out) {
    if (!v || !norm_out) return;
    *norm_out = chord_sqnorm_vec(*v);
}

EXPORT int64_t ulda_shim_get_scalar_norm(int64_t a, int64_t b) {
    zphi temp = {a, b};
    return chord_sqnorm(temp);
}

EXPORT int ulda_shim_verify_horizon(const vec3* v, int check_type) {
    if (!v) return 0;
    
    zphi r = chord_sqnorm_vec(*v);
    if (check_type == 0) { /* Antipodal Rollover Check */
        return (r.a == 7 && r.b == 3);
    } else if (check_type == 1) { /* Mirror Plane Check */
        return (r.a == 3 && r.b == 1);
    }
    return 0;
}
