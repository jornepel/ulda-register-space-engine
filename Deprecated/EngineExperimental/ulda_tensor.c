#include "ulda.h"
#include <stdio.h>
#include <stdint.h>

#define CELL_COUNT 4

typedef struct {
    vec3    coordinate;
    zphi    internal_stress;
    int64_t accumulated_friction;
} tensor_node;

void execute_xtensor_shear(tensor_node *src, tensor_node *dest) {
    zphi cross_talk_factor = zphi_make(0, 1); 
    zphi transfer_vector = zphi_mul(src->coordinate.x, cross_talk_factor);
    dest->coordinate.z = zphi_add(dest->coordinate.z, transfer_vector);
    dest->internal_stress = zphi_add(dest->internal_stress, src->internal_stress);
    dest->accumulated_friction += invariant_offset();
}

int main(void) {
    tensor_node mesh_grid[CELL_COUNT] = {
        {{{10, 0}, {0, 0}, {0, 0}}, {3, 1}, 0}, /* Torus A */
        {{{0, 0}, {60, 0}, {0, 0}}, {7, 3}, 0}, /* Torus B */
        {{{0, 0}, {0, 0}, {1, 1}},  {1, 0}, 0}, /* Torus C */
        {{{7, 3}, {3, 1}, {1, 0}},  {5, 0}, 0}  /* Torus D */
    };

    /* Voer de tensor-koppelingen uit over de 4 kwadranten */
    for (int i = 0; i < CELL_COUNT; i++) {
        int next_quadrant = (i + 1) % CELL_COUNT;
        execute_xtensor_shear(&mesh_grid[i], &mesh_grid[next_quadrant]);
    }

    /* EXPORT NAAR LIVE JSON-KOPPELING */
    FILE *f = fopen("xtensor_live_bridge.json", "w");
    if (!f) {
        printf("[Error] Kan exportbestand niet openen.\n");
        return 1;
    }

    fprintf(f, "[\n");
    for (int i = 0; i < CELL_COUNT; i++) {
        zphi norm = vec3_sqnorm(mesh_grid[i].coordinate);
        fprintf(f, "  {\n");
        fprintf(f, "    \"torus_id\": %d,\n", i);
        fprintf(f, "    \"norm_a\": %lld,\n", (long long)norm.a);
        fprintf(f, "    \"norm_b\": %lld,\n", (long long)norm.b);
        fprintf(f, "    \"friction\": %lld,\n", (long long)mesh_grid[i].accumulated_friction);
        fprintf(f, "    \"stress_a\": %lld,\n", (long long)mesh_grid[i].internal_stress.a);
        fprintf(f, "    \"stress_b\": %lld\n", (long long)mesh_grid[i].internal_stress.b);
        fprintf(f, "  }%s\n", (i == CELL_COUNT - 1) ? "" : ",");
    }
    fprintf(f, "]\n");
    fclose(f);

    printf("[✓] X TENSOR MATRIX EXPORTED: 'xtensor_live_bridge.json' gekoppeld.\n");
    return 0;
}
