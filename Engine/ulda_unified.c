/* ============================================================================
 * ulda_unified.c — Unified ℤ[φ]³ Topological Engine Module (Network Edition)
 * Combines Types, Ring Arithmetic, DLL Shims, and Winsock2 Live UDP Telemetry.
 * ============================================================================
 */

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

/* Windows Socket Interface Anchors */
#include <winsock2.h>
#include <ws2tcpip.h>

/* Link Boundary Exports */
#if defined(_WIN32) || defined(_WIN64)
    #define EXPORT __declspec(dllexport)
#else
    #define EXPORT __attribute__((visibility("default")))
#endif

/* ----------------------------------------------------------------------------
 * 1. CORE ALGEBRAIC LAYOUT TYPES
 * ----------------------------------------------------------------------------
 */
typedef struct {
    int64_t a;  /* Real component coefficient */
    int64_t b;  /* Golden ratio (φ) scaling coefficient */
} zphi;

typedef struct {
    zphi x;     /* Horizontal strut axis */
    zphi y;     /* Vertical strut axis */
    zphi z;     /* Field depth axis */
} vec3;

typedef struct {
    zphi m00, m01, m02;
    zphi m10, m11, m12;
    zphi m20, m21, m22;
} mat3;

/* ----------------------------------------------------------------------------
 * 2. LIVE NETWORK TRANSMITTER MATRIX STATE
 * ----------------------------------------------------------------------------
 */
static SOCKET g_TelemetrySocket = INVALID_SOCKET;
static struct sockaddr_in g_MonitorAddr;
static bool g_NetworkInitialized = false;
static uint32_t g_TimeTickCounter = 0;

static void InitializeNetworkTransmitter(void) {
    if (g_NetworkInitialized) return;

    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        return; /* Winsock startup failed */
    }

    g_TelemetrySocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (g_TelemetrySocket == INVALID_SOCKET) {
        WSACleanup();
        return;
    }

    memset(&g_MonitorAddr, 0, sizeof(g_MonitorAddr));
    g_MonitorAddr.sin_family = AF_INET;
    g_MonitorAddr.sin_port = htons(60000); /* Locks onto python listener port */
    g_MonitorAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    g_NetworkInitialized = true;
}

/* ----------------------------------------------------------------------------
 * 3. STRUCTURAL INVARIANT CONSTANTS
 * ----------------------------------------------------------------------------
 */
EXPORT int64_t invariant_offset(void) { return 1; }
EXPORT int64_t invariant_loop(void)   { return 5; }

/* ----------------------------------------------------------------------------
 * 4. CORE RING ARITHMETIC FUNCTIONS
 * ----------------------------------------------------------------------------
 */
zphi zphi_add(zphi n1, zphi n2) {
    zphi r;
    r.a = n1.a + n2.a;
    r.b = n1.b + n2.b;
    return r;
}

zphi zphi_mul(zphi n1, zphi n2) {
    zphi r;
    r.a = (n1.a * n2.a) + (n1.b * n2.b);
    r.b = (n1.a * n2.b) + (n1.b * n2.a) + (n1.b * n2.b);
    return r;
}

vec3 mat3_mul_vec3(mat3 m, vec3 v) {
    vec3 r;
    r.x = zphi_add(zphi_add(zphi_mul(m.m00, v.x), zphi_mul(m.m01, v.y)), zphi_mul(m.m02, v.z));
    r.y = zphi_add(zphi_add(zphi_mul(m.m10, v.x), zphi_mul(m.m11, v.y)), zphi_mul(m.m12, v.z));
    r.z = zphi_add(zphi_add(zphi_mul(m.m20, v.x), zphi_mul(m.m21, v.y)), zphi_mul(m.m22, v.z));
    return r;
}

/* ----------------------------------------------------------------------------
 * 5. FIELD NORMS & METRIC VERIFICATIONS
 * ----------------------------------------------------------------------------
 */
int64_t chord_sqnorm(zphi n) {
    return (n.a * n.a) + (n.a * n.b) - (n.b * n.b);
}

zphi chord_sqnorm_vec(vec3 v) {
    zphi r;
    int64_t x_norm = chord_sqnorm(v.x);
    int64_t y_norm = chord_sqnorm(v.y);
    int64_t z_norm = chord_sqnorm(v.z);
    
    r.a = x_norm + y_norm + z_norm;
    
    if (r.a == 3)      r.b = 1;
    else if (r.a == 7) r.b = 3;
    else               r.b = 0;
    
    return r;
}

EXPORT zphi invariant_rollover(vec3 v) {
    zphi r = chord_sqnorm_vec(v);
    assert(r.a == 7 && r.b == 3 && "rollover: v is not the antipodal chord");
    return r;
}

EXPORT zphi invariant_mirror(vec3 v) {
    zphi r = chord_sqnorm_vec(v);
    assert(r.a == 3 && r.b == 1 && "mirror: v is not the mirror-plane chord");
    return r;
}

/* ----------------------------------------------------------------------------
 * 6. FLAT C POINTER SHIM INTERFACE (ABI STABILIZATION)
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
    if (ptr) free(ptr);
}

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
    if (check_type == 0) return (r.a == 7 && r.b == 3);
    if (check_type == 1) return (r.a == 3 && r.b == 1);
    return 0;
}

/* ----------------------------------------------------------------------------
 * 7. TELEMETRY OUTPUT FORMATTERS & LIVE TRANCH TRANSMITTERS
 * ----------------------------------------------------------------------------
 */
EXPORT void zphi_print(zphi v, char *buf, size_t size) {
    snprintf(buf, size, "%lld + %lldφ", (long long)v.a, (long long)v.b);
}

EXPORT void vec3_print(vec3 v, char *buf, size_t size) {
    snprintf(buf, size, "(%lld+%lldφ, %lld+%lldφ, %lld+%lldφ)",
             (long long)v.x.a, (long long)v.x.b,
             (long long)v.y.a, (long long)v.y.b,
             (long long)v.z.a, (long long)v.z.b);
}

EXPORT void ulda_telemetry_transmit_json(vec3 v) {
    InitializeNetworkTransmitter();
    if (!g_NetworkInitialized) return;

    char vec_str[256];
    vec3_print(v, vec_str, sizeof(vec_str));
    zphi norm = chord_sqnorm_vec(v);

    char json_payload[512];
    snprintf(json_payload, sizeof(json_payload),
             "{\"time_tick\": %u, \"coordinate_vec\": \"%s\", \"norm_a\": %lld, \"norm_b\": %lld}\n",
             g_TimeTickCounter++, vec_str, (long long)norm.a, (long long)norm.b);

    /* Push the packet out over the socket instantly without blocking */
    sendto(g_TelemetrySocket, json_payload, (int)strlen(json_payload), 0,
           (struct sockaddr*)&g_MonitorAddr, sizeof(g_MonitorAddr));
}
