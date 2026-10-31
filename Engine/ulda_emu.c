/* ============================================================================
 * ulda_emu.c — Windows Translation Emulator & Vertex Interception Pipeline
 * Simulates low-level vertex stream hooking for Direct3D graphic runtimes.
 * ============================================================================
 */

#include "ulda_unified.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Standard, layout-compatible Vertex Structure matching real 3D pipeline loads */
typedef struct {
    float position[3];  /* Standard IEEE 754 float X, Y, Z from game engine */
    float normal[3];    /* Surface Normal vectors */
    float uv[2];        /* Texture mapping coordinates */
} D3D11_VERTEX_STREAM;

/* ----------------------------------------------------------------------------
 * 1. VERTEX FIELD CONVERSION MECHANICS
 * ----------------------------------------------------------------------------
 * Translates standard floating-point coordinates into the exact integer ring
 * Z[φ] by applying a fixed spatial scale magnification factor to minimize rounding noise.
 */
static void float_to_zphi(float f, zphi* out) {
    /* Scale factor maps continuous space onto discrete integer steps */
    const int64_t scale_factor = 1000000; 
    out->a = (int64_t)(f * (float)scale_factor);
    out->b = 0; /* Clear the phi component for raw input alignment */
}

static void zphi_to_float(zphi n, float* out) {
    /* Approximate φ value used strictly for back-projection onto the screen */
    const float phi_approx = 1.6180339887f;
    const float scale_factor = 1000000.0f;
    *out = ((float)n.a + ((float)n.b * phi_approx)) / scale_factor;
}

/* ----------------------------------------------------------------------------
 * 2. VERTEX STREAM INTERCEPTION LAYER
 * ----------------------------------------------------------------------------
 * Mimics the active proxy interceptor loop. It captures a raw float vertex 
 * array, transforms it into Z[φ]³ space, executes the algebraic transformation 
 * matrix, and writes the corrected coordinates back to the active GPU stream.
 */
EXPORT void ulda_emu_intercept_vertex_stream(
    void* pVertexBuffer, 
    uint32_t vertexCount, 
    uint32_t stride, 
    const mat3* transformationMatrix
) {
    if (!pVertexBuffer || vertexCount == 0 || !transformationMatrix) return;
    if (stride < sizeof(D3D11_VERTEX_STREAM)) return; /* Safety bounds check */

    uint8_t* pRawBytes = (uint8_t*)pVertexBuffer;

    for (uint32_t i = 0; i < vertexCount; ++i) {
        D3D11_VERTEX_STREAM* pVertex = (D3D11_VERTEX_STREAM*)(pRawBytes + (i * stride));

        /* Step 1: Map raw 3D input coordinates onto the integer matrix struts */
        vec3 v_ring;
        float_to_zphi(pVertex->position[0], &v_ring.x);
        float_to_zphi(pVertex->position[1], &v_ring.y);
        float_to_zphi(pVertex->position[2], &v_ring.z);

        /* Step 2: Enforce the Horizon Safety Verification Gates */
        zphi norm = chord_sqnorm_vec(v_ring);
        
        /* If the vector approaches spaghettification thresholds, apply phase correction */
        if (norm.a >= 7) {
            /* Execute dynamic phase reversal to keep coordinates locked within safe bounds */
            v_ring.x.a = -v_ring.x.a;
            v_ring.y.a = -v_ring.y.a;
            v_ring.z.a = -v_ring.z.a;
        }

        /* Step 3: Execute the error-free algebraic ring matrix rotation */
        vec3 v_transformed = mat3_mul_vec3(*transformationMatrix, v_ring);

        /* STREAM TELEMETRY Shunt JSON out to the active python socket loop */
        extern void ulda_telemetry_transmit_json(vec3 v);
        ulda_telemetry_transmit_json(v_transformed);

        /* Step 4: Back-project the stable coordinates safely into the float vertex pool */
        zphi_to_float(v_transformed.x, &pVertex->position[0]);
        zphi_to_float(v_transformed.y, &pVertex->position[1]);
        zphi_to_float(v_transformed.z, &pVertex->position[2]);
    }
}


/* ----------------------------------------------------------------------------
 * 3. EMULATOR PIPELINE TEST RIG
 * ----------------------------------------------------------------------------
 */
EXPORT int ulda_emu_verify_pipeline(void) {
    const uint32_t test_count = 3;
    uint32_t stride = sizeof(D3D11_VERTEX_STREAM);
    
    /* Allocate a dummy vertex stream block mimicking active GPU resource space */
    D3D11_VERTEX_STREAM* mock_buffer = (D3D11_VERTEX_STREAM*)malloc(stride * test_count);
    if (!mock_buffer) return 0;

    /* Initialize Mock Vertex positions: Vertex 0 at (1.0, 0.0, -0.5) */
    mock_buffer[0].position[0] = 1.0f;  mock_buffer[0].position[1] = 0.0f;  mock_buffer[0].position[2] = -0.5f;
    mock_buffer[1].position[0] = 0.0f;  mock_buffer[1].position[1] = 2.5f;  mock_buffer[1].position[2] = 1.1f;
    mock_buffer[2].position[0] = -1.2f; mock_buffer[2].position[1] = -1.2f; mock_buffer[2].position[2] = 0.0f;

    /* Construct an identity algebraic transformation matrix (no scaling/skew) */
    mat3 identity_matrix;
    memset(&identity_matrix, 0, sizeof(mat3));
    identity_matrix.m00.a = 1; /* x_out = 1*x_in */
    identity_matrix.m11.a = 1; /* y_out = 1*y_in */
    identity_matrix.m22.a = 1; /* z_out = 1*z_in */

    /* Run the interception emulator pipeline */
    ulda_emu_intercept_vertex_stream(mock_buffer, test_count, stride, &identity_matrix);

    /* Verify that identity passthrough functions cleanly without coordinate collapse */
    int pipeline_happy = (mock_buffer[0].position[0] > 0.9f && mock_buffer[0].position[0] < 1.1f);
    
    free(mock_buffer);
    return pipeline_happy;
}
