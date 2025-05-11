#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "solver.h"
#include "linked_list_map.h"
#include "queue_map.h"
#include "sokoban.h"

bool is_in_explored_list(linked_list_queue list, my_map *map) {
    for (cell_queue *cur = list; cur != NULL; cur = cur->next_cell) {
        if (compare_maps(cur->map, map)) {
            return true;
        }
    }
    return false;
}

void free_solution_path(cell_queue *cell) {
    while (cell != NULL) {
        cell_queue *prev = cell->mother_cell;
        if (cell->map != NULL) {
            free(cell->map->map);
            free(cell->map);
        }
        free(cell);
        cell = prev;
    }
}


bool is_winning_map(my_map *map){

    // Check if the map is a winning plan
    for (int i = 0; i < map->width * map->height; i++){
        if (map->map[i] == '.') return false;
        if (map->map[i] == '$') return false;
        if (map->map[i] == '+') return false;
    }
    return true;
}

char *solver(my_map *initial_map){

    my_map *final_map = NULL;
    cell_queue *final_cell = NULL;

    linked_list_queue search_queue = nil();
    linked_list_queue dequeued_queue = nil();

    linked_list_map explored_list = map_list_nil();

    printf("Inserted map at %p\n", (void*)initial_map);
    explored_list = map_list_insert_element(explored_list, 0, initial_map);

    enqueue(&search_queue, initial_map, ' ', NULL);

    while(!is_empty(search_queue)){

        // dequeue the first element of the queue
        cell_queue *current_cell = dequeue(&search_queue);
        if (current_cell == NULL) break;

        my_map *current_map = current_cell->map;

        enqueue(&dequeued_queue, current_map, current_cell->action, current_cell);

        // check if the map is a winning plan
        if (is_winning_map(current_map)){
            final_map = current_map;
            final_cell = current_cell;
            break;
        }

        char move_list[4] = {'N', 'S', 'E', 'W'};

        // enqueue all possible moves from the current map

        for (int i = 0; i < 4; i++){

            my_map *new_map = move(move_list[i], current_map);

            // printf("New map after move %c:\n", move_list[i]);
            // print_map(new_map);

            if (new_map == NULL) break;

            if (map_list_contains(explored_list, new_map)){
                free(new_map->map);
                free(new_map);
            } else {

                // printf("Map_list_insert_element inserted map at %p\n", (void*)new_map);
                explored_list = map_list_insert_element(explored_list, 0, new_map);

                // printf("Enqueue inserted map at %p\n", (void*)new_map);
                enqueue(&search_queue, new_map, move_list[i], current_cell);

                // free(new_map->map);
                // free(new_map);

            }

        }

    }

    if (is_winning_map(final_map)){

        // reconstruct the path from the winning map to the initial map
        char *path = malloc(sizeof(char) * (final_cell->depth + 1));
        int i = final_cell->depth-1; // -2 because the last action is not needed

        while (final_cell->mother_cell != NULL) {
            path[i--] = final_cell->action;
            final_cell = final_cell->mother_cell;
        }
        path[final_cell->depth-1] = '\0';

        // free the memory allocated for the queue and the explored list
        map_list_deallocate_list(explored_list);

        deallocate_list(search_queue);
        deallocate_list(dequeued_queue);

        return path;
    }

    // Free memory in case of failure
    map_list_deallocate_list(explored_list);

    deallocate_list(search_queue);
    deallocate_list(dequeued_queue);
    free_solution_path(final_cell);

    return NULL;

}