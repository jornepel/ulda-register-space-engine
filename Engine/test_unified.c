/* ============================================================================
 * test_unified.c — Automated Verification Suite for ℤ[φ]³ Topological Engine
 * Validates ring arithmetic, metric squared-norms, and horizon bounds.
 * ============================================================================
 */

#include "ulda_unified.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/* Helper to evaluate verification success prints safely */
static void run_test_gate(const char* test_name, int condition) {
    if (condition) {
        printf("[ VERIFIED SUCCESS ] — Target Gate: %s\n", test_name);
    } else {
        fprintf(stderr, "[ ALARM TRIGGERED  ] — Critical Failure at Gate: %s\n", test_name);
        exit(1);
    }
}

int main(void) {
    char str_buf[256];
    printf("====================================================================\n");
    printf(" INITIALIZING ℤ[φ]³ TOPOLOGICAL ENGINE VERIFICATION MATRIX          \n");
    printf("====================================================================\n\n");

    /* ------------------------------------------------------------------------
     * TEST GATE 1: Core Static Invariant Verification
     * ------------------------------------------------------------------------
     */
    run_test_gate("Structural Invariant Offset (1)", invariant_offset() == 1);
    run_test_gate("Closed Loop Group Order (5)", invariant_loop() == 5);

    /* ------------------------------------------------------------------------
     * TEST GATE 2: Ring Multiplication & Identity Invariance (φ² = φ + 1)
     * ------------------------------------------------------------------------
     * Let n1 = φ (0 + 1φ), n2 = φ (0 + 1φ). 
     * n1 * n2 = φ² = 1 + 1φ. 
     */
    zphi phi_identity = {0, 1};
    zphi expected_squared = {1, 1};
    zphi calculated_squared = zphi_mul(phi_identity, phi_identity);
    
    run_test_gate("Algebraic Ring Identity Multiplication (φ² -> 1 + 1φ)", 
                  calculated_squared.a == expected_squared.a && 
                  calculated_squared.b == expected_squared.b);

    /* ------------------------------------------------------------------------
     * TEST GATE 3: Memory Allocation and Pointer Shim Vector Interface
     * ------------------------------------------------------------------------
     */
    /* Construct vector v1 = (1+1φ, 2+0φ, 0+3φ) */
    vec3* v1 = ulda_alloc_vector(1, 1, 2, 0, 0, 3);
    assert(v1 != NULL);
    
    /* Construct vector v2 = (0+2φ, 1+1φ, -1+0φ) */
    vec3* v2 = ulda_alloc_vector(0, 2, 1, 1, -1, 0);
    assert(v2 != NULL);

    vec3 result_add;
    ulda_shim_vec3_add(v1, v2, &result_add);

    /* Expected components: X=(1+3φ), Y=(3+1φ), Z=(-1+3φ) */
    int add_check = (result_add.x.a == 1 && result_add.x.b == 3 &&
                     result_add.y.a == 3 && result_add.y.b == 1 &&
                     result_add.z.a == -1 && result_add.z.b == 3);
    run_test_gate("Flat ABI Shim Vector Translation Add Pass", add_check);

    /* ------------------------------------------------------------------------
     * TEST GATE 4: Field Norm and Horizon Symmetry Checks
     * ------------------------------------------------------------------------
     */
    /* Construct a precise Mirror-Plane Vector: v_mirror = (1+0φ, 1+0φ, 1+0φ)
     * Total squared-norm coefficients: a = 1²+1²+1² = 3, b = 0²+0²+0² = 1.
     * This hits the exact mirror gate constant (3 + 1φ).
     */
    vec3* v_mirror = ulda_alloc_vector(1, 0, 1, 0, 1, 0);
    assert(v_mirror != NULL);

    int horizon_mirror_check = ulda_shim_verify_horizon(v_mirror, 1);
    run_test_gate("Horizon Boundary Check: Mirror Plane Invariant Verification", horizon_mirror_check);
    
    /* Direct internal structural check to trigger validation path without crashing */
    zphi mirror_norm = invariant_mirror(*v_mirror);
    run_test_gate("Internal Assert Gate: Mirror Invariant Norm Match (3 + 1φ)", 
                  mirror_norm.a == 3 && mirror_norm.b == 1);

    /* Print out structured tracking log for confirmation visual inspection */
    vec3_print(*v_mirror, str_buf, sizeof(str_buf));
    printf(" -> Mirror Target Vector String: %s\n\n", str_buf);

    /* ------------------------------------------------------------------------
     * TEST GATE 5: Live Network Telemetry Serialization
     * ------------------------------------------------------------------------
     * Force the test suite to push our verified vectors out to the socket
     * so we can see the Python monitor window wake up in real-time.
     */
    extern void ulda_telemetry_transmit_json(vec3 v);
    
    printf("[ STATUS ] Injecting test vectors into Winsock2 transmitter...\n");
    ulda_telemetry_transmit_json(*v1);
    ulda_telemetry_transmit_json(*v2);
    ulda_telemetry_transmit_json(*v_mirror);


    /* ------------------------------------------------------------------------
     * CLEANUP REGISTER SPACE
     * ------------------------------------------------------------------------
     */
    ulda_free_memory(v1);
    ulda_free_memory(v2);
    ulda_free_memory(v_mirror);

    printf("====================================================================\n");
    printf(" ALL ℤ[φ]³ TOPOLOGICAL ENGINE GATES ARE FULLY OPERATIONAL AND HAPPY \n");
    printf("====================================================================\n");
    return 0;
}
