#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "sokoban.h"

int main(void)

{

    my_map *map_initiale = malloc(sizeof(my_map));
    my_map *r = malloc(sizeof(my_map));

    char *q = "soko_dumb.in";

    map_initiale->height = 10;
    map_initiale->width = 8;
    map_initiale->hposition = 4;
    map_initiale->vposition = 7;
    map_initiale->map = q;

    r->height = 10;
    r->width = 8;
    r->hposition = 4;
    r->vposition = 7;
    r->map = "soko_dumb_1.in";

    my_map *p = replay(map_initiale, 3, "SSSEENN");

    printf(" | test du replay...");

    assert(comparaison_struct(p, r));
    
    printf("OK!\n");

    free(p);
    free(q);
    free(map_initiale);
    free(r);

    return 0;
}