#include <stdio.h>
#include <stdlib.h>
#include "sokoban.h"
#include "solver.h"
#include "loader.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s fichier_niveau.in\n", argv[0]);
        return EXIT_FAILURE;
    }

    int width, height, x = 0, y = 0;
    char *level = NULL;

    if (!load_level(argv[1], &width, &height, &level, &x, &y)) {
        fprintf(stderr, "Erreur chargement niveau : %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    // Create the initial map structure
    my_map *initial_map = malloc(sizeof(my_map));
    initial_map->width = width;
    initial_map->height = height;
    initial_map->map = level;
    initial_map->hposition = x;
    initial_map->vposition = y;

    int explored_count = 0;
    char *solution = solver(initial_map, &explored_count);

    if (solution) {
        printf("Solution found: %s\n", solution);
        free(solution);
    } else {
        printf("No solution found.\n");
    }

    printf("Maps explored: %d\n", explored_count);

    return EXIT_SUCCESS;
}