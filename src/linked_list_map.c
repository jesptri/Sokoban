/**
 * @file linked_list_int_fun.c
 *
 * @ingroup in101-labs
 *
 * @brief Simple implementation of a linked list
 *
 * The implementation of the linked list (functional version).
 */

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linked_list_map.h"
#include "sokoban.h"

// utilitary functions goes here

bool compare_maps(my_map *map1, my_map *map2) {
    if (map1 == NULL || map2 == NULL) return false;

    if (map1->width != map2->width || map1->height != map2->height) return false;

    if (map1->hposition != map2->hposition || map1->vposition != map2->vposition) return false;

    int size = map1->width * map1->height;
    if (memcmp(map1->map, map2->map, size) != 0) return false;

    return true;
}

cell_map * map_list_go_to_position(linked_list_map list, int pos){
    cell_map * p_current_cell = list;

    for (int i = 0; i < pos; i++) {
        p_current_cell = p_current_cell->next;
    }

    return p_current_cell;
}

bool map_list_contains(linked_list_map list, my_map *map) {
    for (cell_map *cur = list; cur != NULL; cur = cur->next) {
        if (compare_maps(cur->map, map)) {
            return true;
        }
    }
    return false;
}


// functions from the signature
linked_list_map map_list_nil(){
    return NULL;
}

linked_list_map map_list_cons(linked_list_map list, my_map *MAP){
    cell_map *p_new_cell = malloc(sizeof(cell_map));

    if (p_new_cell == NULL) {
        printf("problem with creating cell in cons!\n");
    }

    p_new_cell->map = MAP;
    p_new_cell->next  = list;

    return p_new_cell;
}

int map_list_size(linked_list_map list){
    int length = 0;
    cell_map * p_current_cell = list;

    while (p_current_cell != NULL) {
        p_current_cell = p_current_cell->next;
        length++;
    }

    return length;
}

bool map_list_is_empty(linked_list_map list){
    return list == NULL;
}

my_map *map_list_get_element(linked_list_map list, int pos){

    int length = map_list_size(list);

    assert(! map_list_is_empty(list) && pos >= 0 && pos < length);

    // go to position
    cell_map *p_cell = map_list_go_to_position(list, pos);

    return p_cell->map;
}

linked_list_map map_list_insert_element(linked_list_map list, int pos, my_map * MAP){
    // not very efficient to use size function but...
    int length = map_list_size(list);

    assert(pos >= 0 && pos <= length);

    if (pos == 0) {
        return map_list_cons(list, MAP);
    }

    cell_map *p_current_cell = list;
    cell_map *p_new_cell = malloc(sizeof(cell_map));

    if (p_new_cell == NULL) {
        printf("problem with creating cell in insert_element!\n");
    }

    p_new_cell->map = MAP;

    p_current_cell = map_list_go_to_position(list, pos - 1);

    p_new_cell->next = p_current_cell->next;
    p_current_cell->next = p_new_cell;

    return list;
}

linked_list_map map_list_remove_element(linked_list_map list, int pos){

    cell_map *p_current_cell = list;
    cell_map *p_old_cell     = NULL;

    int length = map_list_size(list);

    assert(! map_list_is_empty(list) && pos >= 0 && pos < length);

    if (pos == 0){
        linked_list_map tail = p_current_cell->next;

        free(p_current_cell->map);
        free(p_current_cell);

        return tail;
    }

    p_current_cell = map_list_go_to_position(list, pos - 1);
    p_old_cell = p_current_cell->next;
    p_current_cell->next = p_old_cell->next;

    free(p_old_cell->map);
    free(p_old_cell);

    return list;
}

void map_list_deallocate_list(linked_list_map list){

    cell_map *p_temp_cell = NULL;
    cell_map *p_current_cell = list;

    while (p_current_cell != NULL) {
        p_temp_cell = p_current_cell;
        p_current_cell = p_current_cell->next;
        free(p_temp_cell->map);
        free(p_temp_cell);
    }
}

// int main(void){
//     return 0;
// }