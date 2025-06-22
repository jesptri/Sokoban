#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <assert.h>

#include "loader.h"
#include "linked_list_map.h"
#include "sokoban.h"

int main(void){

    printf(" | Test de linked_map...\n");

    linked_list_map l_map = map_list_nil();

    // both * my_map constituting linked_list_map

    my_map *L_1 = loader("data/soko1.in");
    my_map *L_2 = loader("data/soko2.in");

    l_map = map_list_cons(l_map, L_1);
    l_map = map_list_cons(l_map, L_2);
    
    my_map *L = map_list_get_element(l_map, 1);

    // checking if both my_map are similar
    assert(L_1->map == L->map);

    map_list_deallocate_list(l_map);

    printf(" | OK!\n");

    return 0;

}