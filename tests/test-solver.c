#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "loader.h"
#include "sokoban.h"
#include "solver.h"

int main() {

    printf("Loading the map for data/soko_dumb.in...\n");
    my_map *map = loader("data/soko_dumb.in");
    assert(map != NULL);

    printf("Calling the solver...\n");
    char *solution = solver(map);
    printf("Solver is back.\n");

    if (solution != NULL) {

        printf("Solution found! %s\n", solution);
        printf("Replaying the solution...\n");

        my_map *map_second_call = loader("data/soko_dumb.in");
        my_map *replayed_map = replay(map_second_call, 100, solution);

        if(is_winning_map(replayed_map)){
            printf("The plan leads well to a winning map!\n");
        } else {
            printf("There is an issue, the plan does not lead to a winning map...\n");
        }

        free(replayed_map->map);
        free(replayed_map);
        free(map_second_call->map);
        free(map_second_call);

    } else {

        printf("No solution found.\n");

    }

    free(solution);

    return 0;
}
