#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "loader.h"
#include "sokoban.h"
#include "solver.h"

int main() {
    printf("Loading the map...\n");
    my_map *map = loader("data/soko_dumb.in");
    assert(map != NULL);  // ← Stoppe ici si map est NULL

    printf("Calling the solver...\n");
    char *solution = solver(map);
    printf("Solver is back.\n");

    if (solution != NULL) {
        printf("Solution found! %s\n", solution);
        free(solution);
    } else {
        printf("No solution found.\n");
    }

    return 0;
}
