#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h> 

#include "sokoban.h"
#include "loader.h"

int main(void)

{
    printf(" | test du loader...\n");

    my_map *result = loader("data/soko1.in");

    print_map(result);

    printf(" | OK!\n");

    return 0;
}