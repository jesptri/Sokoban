#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "loader.h"
#include "sokoban.h"
#include "solver.h"

int main() {
    printf("Chargement de la map...\n");
    my_map *map = loader("data/soko_dumb.in");
    assert(map != NULL);  // ← Stoppe ici si map est NULL

    printf("Appel du solver...\n");
    char *solution = solver(map);
    printf("Retour du solver.\n");

    if (solution != NULL) {
        printf("Plan trouvé : %s\n", solution);
        free(solution);
    } else {
        printf("Aucune solution trouvée.\n");
    }

    return 0;
}
