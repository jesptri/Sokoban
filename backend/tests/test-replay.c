#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "sokoban.h"
#include "loader.h"

int main(void) {
    printf(" | Replay tests:\n");

    // Test 1
    my_map *initial_map_1 = loader("data/soko_dumb.in");
    my_map *final_map_1 = loader("data/soko_dumb_1.in");
    my_map *result_map_1 = replay(initial_map_1, 3, "SSSEENN");
    assert(strcmp(final_map_1->map, result_map_1->map) == 0);
    printf(" | Test 1 (3 moves) OK!\n");

    free(initial_map_1->map); free(initial_map_1);
    free(final_map_1->map); free(final_map_1);
    free(result_map_1->map); free(result_map_1);

    // Test 2
    my_map *initial_map_2 = loader("data/soko_dumb.in");
    my_map *final_map_2 = loader("data/soko_dumb_2.in");
    my_map *result_map_2 = replay(initial_map_2, 5, "SSSEENN");
    assert(strcmp(final_map_2->map, result_map_2->map) == 0);
    printf(" | Test 2 (5 moves) OK!\n");

    free(initial_map_2->map); free(initial_map_2);
    free(final_map_2->map); free(final_map_2);
    free(result_map_2->map); free(result_map_2);

    // Test 3
    my_map *initial_map_3 = loader("data/soko_dumb.in");
    my_map *final_map_3 = loader("data/soko_dumb_win.in");
    my_map *result_map_3 = replay(initial_map_3, 7, "SSSEENN");
    assert(strcmp(final_map_3->map, result_map_3->map) == 0);
    printf(" | Test 3 (7 moves, win) OK!\n");

    free(initial_map_3->map); free(initial_map_3);
    free(final_map_3->map); free(final_map_3);
    free(result_map_3->map); free(result_map_3);

    // Test 4
    my_map *initial_map_4 = loader("data/soko_dumb.in");
    my_map *final_map_4 = loader("data/soko_dumb_3.in");
    my_map *result_map_4 = replay(initial_map_4, 7, "ESEESSWNN");
    assert(strcmp(final_map_4->map, result_map_4->map) == 0);
    printf(" | Test 4 (9 moves) OK!\n");

    free(initial_map_4->map); free(initial_map_4);
    free(final_map_4->map); free(final_map_4);
    free(result_map_4->map); free(result_map_4);

    // Test 5
    my_map *initial_map_5 = loader("data/soko_dumb.in");
    my_map *final_map_5 = loader("data/soko_dumb_win.in");
    my_map *result_map_5 = replay(initial_map_5, 9, "ESEESSWNN");
    assert(strcmp(final_map_5->map, result_map_5->map) == 0);
    printf(" | Test 5 (9 moves, win) OK!\n");

    free(initial_map_5->map); free(initial_map_5);
    free(final_map_5->map); free(final_map_5);
    free(result_map_5->map); free(result_map_5);

    return 0;
}