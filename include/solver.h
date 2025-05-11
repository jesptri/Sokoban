#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct my_map my_map;

typedef struct cell_queue cell_queue;

typedef struct stats stats;

struct stats{

    // true: there is a winning plan
    bool winning;
    // a pointer to the map that is considered
    my_map * map;

};

bool is_winning_map(my_map * map);

void free_solution_path(cell_queue *cell);

char *solver(my_map *initial_map);