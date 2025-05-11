#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "queue_map.h"

cell_queue *go_to_position(linked_list_queue list, int pos) {
    cell_queue *p = list;
    for (int i = 0; i < pos; i++) {
        p = p->next_cell;
    }
    return p;
}

linked_list_queue nil() {
    return NULL;
}

int size(linked_list_queue list) {
    int count = 0;
    for (cell_queue *cur = list; cur != NULL; cur = cur->next_cell) {
        count++;
    }
    return count;
}

bool is_empty(linked_list_queue list) {
    return list == NULL;
}

linked_list_queue get_element(linked_list_queue list, int pos) {
    int length = size(list);
    assert(!is_empty(list) && pos >= 0 && pos < length);
    return go_to_position(list, pos);
}

void enqueue(linked_list_queue *list, my_map *MAP, char action, cell_queue *mother) {
    cell_queue *new_cell = malloc(sizeof(cell_queue));
    if (!new_cell) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }

    new_cell->map = MAP;
    new_cell->mother_cell = mother;
    new_cell->action = action;
    new_cell->depth = (mother == NULL) ? 0 : mother->depth + 1;
    new_cell->next_cell = NULL;

    // printf("Enqueued: action=%c, depth=%d\n", action, new_cell->depth);

    if (*list == NULL) {
        *list = new_cell;
    } else {
        cell_queue *current = *list;
        while (current->next_cell != NULL) {
            current = current->next_cell;
        }
        current->next_cell = new_cell;
    }
}

cell_queue *dequeue(linked_list_queue *list) {
    if (*list == NULL) return NULL;

    cell_queue *first = *list;
    *list = first->next_cell;
    first->next_cell = NULL;
    return first;
}

void deallocate_list(linked_list_queue list) {
    cell_queue *cur = list;
    while (cur != NULL) {
        cell_queue *next = cur->next_cell;
        free(cur);
        cur = next;
    }
}

// int main(void){
//     return 0;
// }