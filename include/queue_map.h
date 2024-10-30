#include <stdio.h>
#include <stdlib.h>



// queue_map started but far from being finished !



typedef struct my_map my_map;

struct cell_queue
{
    // a pointer to a map
    my_map * map;
    // a pointer to the next cell in the queue
    cell_queue * next_cell;
    // a pointer to the mother cell of the considered cell
    cell_queue * mother_cell;
    // action that generated the considered cell
    
    // depth of the cell
    int depth;

}

typedef cell_queue * linked_list_queue;

