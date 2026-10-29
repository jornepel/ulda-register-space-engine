/* ulda_shim.c — flat C interface so Python (ctypes) can call the engine.
 *
 * Why a shim and not chord_sqnorm directly? ctypes can't pass C structs
 * by value cleanly. We flatten O and Q to 12 int64s and return the result
 * through two output pointers.
 */
#include "ulda.h"

void chord_sqnorm_flat(
    long long ox_a, long long ox_b,
    long long oy_a, long long oy_b,
    long long oz_a, long long oz_b,
    long long qx_a, long long qx_b,
    long long qy_a, long long qy_b,
    long long qz_a, long long qz_b,
    long long *out_a, long long *out_b
) {
    vec3 O = {{ox_a, ox_b}, {oy_a, oy_b}, {oz_a, oz_b}};
    vec3 Q = {{qx_a, qx_b}, {qy_a, qy_b}, {qz_a, qz_b}};
    zphi r = chord_sqnorm(O, Q);
    *out_a = r.a;
    *out_b = r.b;
}
