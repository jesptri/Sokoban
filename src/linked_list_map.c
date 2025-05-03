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

#include "linked_list_map.h"

// utilitary functions goes here
cell_map * go_to_position(linked_list_map list, int pos){
    cell_map * p_current_cell = list;

    for (int i = 0; i < pos; i++) {
        p_current_cell = p_current_cell->next;
    }

    return p_current_cell;
}

// functions from the signature
linked_list_map nil(){
    return NULL;
}

linked_list_map cons(linked_list_map list, my_map * MAP){
    cell_map *p_new_cell = malloc(sizeof(cell_map));

    if (p_new_cell == NULL) {
        printf("problem with creating cell in cons!\n");
    }

    p_new_cell->map = MAP;
    p_new_cell->next  = list;

    return p_new_cell;
}

int size(linked_list_map list){
    int length = 0;
    cell_map * p_current_cell = list;

    while (p_current_cell != NULL) {
        p_current_cell = p_current_cell->next;
        length++;
    }

    return length;
}

bool is_empty(linked_list_map list){
    return list == NULL;
}

my_map * get_element(linked_list_map list, int pos){

    int length = size(list);

    assert(! is_empty(list) && pos >= 0 && pos < length);

    // go to position
    cell_map *p_cell = go_to_position(list, pos);

    return p_cell->map;
}

linked_list_map insert_element(linked_list_map list, int pos, my_map * MAP){
    // not very efficient to use size function but...
    int length = size(list);

    assert(pos >= 0 && pos <= length);

    if (pos == 0) {
        return cons(list, MAP);
    }

    cell_map *p_current_cell = list;
    cell_map *p_new_cell = malloc(sizeof(cell_map));

    if (p_new_cell == NULL) {
        printf("problem with creating cell in insert_element!\n");
    }

    p_new_cell->map = MAP;

    p_current_cell = go_to_position(list, pos - 1);

    p_new_cell->next = p_current_cell->next;
    p_current_cell->next = p_new_cell;

    return list;
}

linked_list_map remove_element(linked_list_map list, int pos){

    cell_map *p_current_cell = list;
    cell_map *p_old_cell     = NULL;

    int length = size(list);

    assert(! is_empty(list) && pos >= 0 && pos < length);

    if (pos == 0){
        linked_list_map tail = p_current_cell->next;

        free(p_current_cell->map);
        free(p_current_cell);

        return tail;
    }

    p_current_cell = go_to_position(list, pos - 1);
    p_old_cell = p_current_cell->next;
    p_current_cell->next = p_old_cell->next;

    free(p_old_cell->map);
    free(p_old_cell);

    return list;
}

void deallocate_list(linked_list_map list){

    cell_map *p_temp_cell = NULL;
    cell_map *p_current_cell = list;

    while (p_current_cell != NULL) {
        p_temp_cell    = p_current_cell;
        p_current_cell = p_current_cell->next;
        free(p_temp_cell->map);
        free(p_temp_cell);
    }
}