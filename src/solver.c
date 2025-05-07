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

bool compare_maps(my_map *map1, my_map *map2) {
    if (map1 == NULL || map2 == NULL) return false;

    if (map1->width != map2->width || map1->height != map2->height) return false;

    if (map1->hposition != map2->hposition || map1->vposition != map2->vposition) return false;

    int size = map1->width * map1->height;
    if (memcmp(map1->map, map2->map, size) != 0) return false;

    return true;
}


bool is_winning_map(my_map * map){
    // Check if the map is a winning plan
    for (int i = 0; i < map->width * map->height; i++){
        if (map->map[i] == '.') return false;
        if (map->map[i] == '$') return false;
        if (map->map[i] == '+') return false;
    }
    return true;
}

char *solver(my_map *initial_map){

    my_map *final_map = malloc(sizeof(my_map));
    cell_queue *final_cell = malloc(sizeof(cell_queue));


    linked_list_queue search_queue = nil();
    linked_list_queue dequeued_queue = nil();

    linked_list_map explored_list = map_list_nil();

    enqueue(&search_queue, initial_map, ' ');

    while(!is_empty(search_queue)){

        cell_queue *current_cell = malloc(sizeof(cell_queue));

        // dequeue the first element of the queue
        current_cell = dequeue(&search_queue);

        my_map *current_map = current_cell->map;

        enqueue(&dequeued_queue, current_map, dequeued_queue->action);

        // check if the map is a winning plan
        if (is_winning_map(current_map)){
            break;
        }

        char move_list[4] = {'N', 'S', 'E', 'W'};

        // enqueue all possible moves from the current map

        for (int i = 0; i < 4; i++){
            my_map *new_map = move(move_list[i], current_map);

            if (map_list_contains(explored_list, new_map)){
                free(new_map->map);
                free(new_map);
                continue;
            }

            explored_list = map_list_insert_element(explored_list, 0, new_map);
            enqueue(&search_queue, new_map, move_list[i]);

        }

        final_map = current_map;
        final_cell = current_cell;

    }

    if (is_winning_map(final_map)){
        // reconstruct the path from the winning map to the initial map
        char *path = malloc(sizeof(char) * (final_cell->depth + 1));
        int i = 0;
        while (final_cell != NULL){
            path[i] = final_cell->action;
            final_cell = final_cell->mother_cell;
            i++;
        }
        path[i] = '\0';
        return path;
    } else {
        return NULL;
    }


    // free the memory allocated for the queue and the explored list
    deallocate_list(search_queue->mother_cell);
    deallocate_list(search_queue->next_cell);
    map_list_deallocate_list(explored_list);
    free(search_queue);
    free(dequeued_queue);

    return NULL;

}