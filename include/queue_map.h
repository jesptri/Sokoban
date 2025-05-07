#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct my_map my_map;

typedef struct cell_queue {
    my_map *map;
    struct cell_queue *mother_cell;
    char action;
    int depth;
    struct cell_queue *next_cell;
} cell_queue;

typedef cell_queue *linked_list_queue;

cell_queue *go_to_position(linked_list_queue list, int pos);

linked_list_queue nil();

int size(linked_list_queue list);

bool is_empty(linked_list_queue list);

linked_list_queue get_element(linked_list_queue list, int pos);

void enqueue(linked_list_queue *list, my_map *MAP, char action);

cell_queue *dequeue(linked_list_queue *list);

void deallocate_list(linked_list_queue list);
