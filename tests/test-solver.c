#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "loader.h"
#include "sokoban.h"
#include "solver.h"

int main() {
    // Charger une map de test
    my_map *map = loader("data/soko_dumb.in");

    // Appeler le solver
    char *solution = solver(map);

    if (solution != NULL) {
        printf("Plan trouvé : %s\n", solution);
        free(solution);
    } else {
        printf("Aucune solution trouvée.\n");
    }

    return 0;
}
