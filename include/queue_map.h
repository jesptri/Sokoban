#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct my_map my_map;

typedef struct cell_queue cell_queue;

struct cell_queue{

    // a pointer to a map
    my_map * map;
    // a pointer to the mother cell of the considered cell
    cell_queue * mother_cell;
    // action that generated the considered cell
    char action;  
    // depth of the cell
    int depth;
    // a pointer to the next cell in the queue
    cell_queue * next_cell;

};

typedef cell_queue * linked_list_queue;

cell_queue * go_to_position(linked_list_queue list, int pos);

linked_list_queue nil();

int size(linked_list_queue list);

bool is_empty(linked_list_queue list);

linked_list_queue get_element(linked_list_queue list, int pos);

linked_list_queue enqueue(linked_list_queue list, my_map * MAP, char action);

linked_list_queue dequeue(linked_list_queue list);

void deallocate_list(linked_list_queue list);
