#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "queue_map.h"


cell_queue * go_to_position(linked_list_queue list, int pos){
    cell_queue * p_current_cell = list;

    for (int i = 0; i < pos; i++) {
        p_current_cell = p_current_cell->next_cell;
    }

    return p_current_cell;
}

linked_list_queue nil(){
    return NULL;
}

int size(linked_list_queue list){
    int length = 0;
    cell_queue * p_current_cell = list;

    while (p_current_cell != NULL) {
        p_current_cell = p_current_cell->next_cell;
        length++;
    }

    return length;
}

bool is_empty(linked_list_queue list){
    return list == NULL;
}

linked_list_queue get_element(linked_list_queue list, int pos){

    int length = size(list);

    assert(! is_empty(list) && pos >= 0 && pos < length);

    // go to position
    cell_queue *p_cell = go_to_position(list, pos);

    return p_cell;
}

linked_list_queue enqueue(linked_list_queue list, my_map *MAP, char action) {
    cell_queue *new_cell = malloc(sizeof(cell_queue));
    if (!new_cell) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }

    new_cell->map = MAP;
    new_cell->mother_cell = NULL;
    new_cell->action = action;
    new_cell->depth = (list ? size(list) : 0);
    new_cell->next_cell = NULL;

    if (list == NULL) {
        return new_cell;
    }

    cell_queue *current = list;
    while (current->next_cell != NULL) {
        current = current->next_cell;
    }
    current->next_cell = new_cell;

    return list;
}

linked_list_queue dequeue(linked_list_queue list) {
    if (list == NULL) return NULL;

    cell_queue *next = list->next_cell;
    free(list);
    return next;
}

void deallocate_list(linked_list_queue list){

    cell_queue *current = list;
    while (current != NULL) {
        cell_queue *next = current->next_cell;
        free(current);
        current = next;
    }

}
