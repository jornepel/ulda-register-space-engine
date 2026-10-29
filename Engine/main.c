/* ========================================================================
 * main.c — ULDA Phase-Locked Simulation Loop Runner
 * ======================================================================== */
#include "ulda.h"
#include <stdio.h>
#include <stdbool.h>

#define QUADRANTS 4

/* Each quadrant holds an active spatial state vector and a gear spin direction */
typedef struct {
    vec3    state;
    int8_t  gear_spin; /* +1 for clockwise, -1 for counter-clockwise */
    int64_t rank_n;    /* Exponential time ladder tier: 60^n */
} toroidal_cell;

/* Global state: The 2x2 mesh network */
static toroidal_cell mesh[QUADRANTS];

void init_mesh(void) {
    // Spatial Carrier initialization (Anchor at baseline 60Hz energy scale)
    zphi seed = zphi_make(1, 0); 
    
    mesh[0] = (toroidal_cell){{seed, zphi_make(0,0), zphi_make(0,0)},  1, 1}; // Torus A
    mesh[1] = (toroidal_cell){{zphi_make(0,0), seed, zphi_make(0,0)}, -1, 1}; // Torus B (Counter-Rotated)
    mesh[2] = (toroidal_cell){{zphi_make(0,0), zphi_make(0,0), seed}, -1, 1}; // Torus C (Counter-Rotated)
    mesh[3] = (toroidal_cell){{seed, seed, seed},                      1, 1}; // Torus D
    
    printf("[System Initialized] 2x2 Quad-Toroidal Network Active.\n\n");
}

void step_network(int64_t tick) {
    zphi phi_factor = zphi_make(0, 1); // Pure φ step multiplier
    int64_t offset = invariant_offset();
    int64_t loop_order = invariant_loop();

    char z_buf[64];
    char v_buf[256];

    for (int i = 0; i < QUADRANTS; i++) {
        // Apply directional velocity driven by the counter-rotational gears
        zphi delta = zphi_make(offset * mesh[i].gear_spin, 0);
        mesh[i].state.x = zphi_add(mesh[i].state.x, delta);
        mesh[i].state.y = zphi_add(mesh[i].state.y, zphi_mul(delta, phi_factor));
        
        // Read out the current metric invariant of the active chord
        zphi current_norm = vec3_sqnorm(mesh[i].state);

        // Check topological boundary: Mirror Plane Collision (3 + 1φ)
        if (current_norm.a == 3 && current_norm.b == 1) {
            zphi_print(current_norm, z_buf, sizeof(z_buf));
            printf("[TICK %04lld] [Torus %d] MIRROR PLANE INTERSECTION reached: %s\n", (long long)tick, i, z_buf);
            
            // Execute inversion phase-lock cross-talk with neighbor quadrant (X Tensor)
            int neighbor = (i + 1) % QUADRANTS;
            mesh[neighbor].state.z = zphi_add(mesh[neighbor].state.z, mesh[i].state.x);
        }

        // Check ultimate topological boundary: Antipodal Rollover (7 + 3φ)
        if (current_norm.a == 7 && current_norm.b == 3) {
            zphi_print(current_norm, z_buf, sizeof(z_buf));
            vec3_print(mesh[i].state, v_buf, sizeof(v_buf));
            
            printf("[TICK %04lld] [Torus %d] ANTIPODAL ROLLOVER CRITICAL NODE: %s\n", (long long)tick, i, z_buf);
            printf("            Vector coordinates: %s\n", v_buf);
            
            // Collapse spatial coordinates and execute Macro Rank Shift down the ladder (60^n)
            mesh[i].rank_n += loop_order; // Shift up by the group order 5
            printf("            Rank Shift Triggered! Escalating to Ladder Tier 60^%lld\n", (long long)mesh[i].rank_n);
            
            // Compress vector back to the horizon seed via dimensional scaling (Inside-Out Phase inversion)
            mesh[i].state.x = zphi_make(1, 0);
            mesh[i].state.y = zphi_make(0, 0);
            mesh[i].state.z = zphi_make(0, 0);
        }
    }
}

int main(void) {
    init_mesh();
    
    // Run the engine for a sample cycle of 50 harmonic ticks
    for (int64_t t = 1; t <= 50; t++) {
        step_network(t);
    }
    
    return 0;
}
