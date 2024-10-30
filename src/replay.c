#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sokoban.h"
#include "loader.h"


int main(int argc, char *argv[])
{
    
    int direction = strtol(argv[2], NULL, 1);

    my_map *map = loader(argv[1]);

    my_map *p = replay(map, direction, argv[3]);

    print_map(p);
    
    return 0;
}