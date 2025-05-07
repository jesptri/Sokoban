#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct my_map my_map;

typedef struct stats stats;

struct stats{

    // true: there is a winning plan
    bool winning;
    // a pointer to the map that is considered
    my_map * map;

};

bool is_winning_map(my_map * map);

bool compare_maps(my_map *map1, my_map *map2);

char *solver(my_map *initial_map);