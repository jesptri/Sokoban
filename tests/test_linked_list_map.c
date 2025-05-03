#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <assert.h>

#include "loader.h"
#include "linked_list_map.h"
#include "sokoban.h"

int main(void){

    printf(" | test de linked_map...\n");

    linked_list_map l_map = malloc(sizeof(linked_list_map));

    my_map * L_1 = malloc(sizeof(my_map));
    my_map * L_2 = malloc(sizeof(my_map));
    my_map * L = malloc(sizeof(my_map));

    l_map = nil();

    // both * my_map constituting linked_list_map

    L_1 = loader("data/soko1.in");
    L_2 = loader("data/soko2.in");

    l_map = cons(l_map, L_1);
    l_map = cons(l_map, L_2);
    
    L = get_element(l_map, 1);

    // checking if both my_map are similar

    assert(L_1->map == L->map);

    printf(" | OK!\n");

    return 0;

}