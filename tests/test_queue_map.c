#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "loader.h"
#include "queue_map.h"
#include "sokoban.h"

int main(void) {
    printf(" | Début des tests de linked_list_queue...\n");

    linked_list_queue queue = nil();

    printf(" | Test de is_empty sur file vide...\n");
    assert(is_empty(queue));
    printf(" | OK!\n");

    printf(" | Test de size sur file vide...\n");
    assert(size(queue) == 0);
    printf(" | OK!\n");

    my_map *L1 = loader("data/soko1.in");
    my_map *L2 = loader("data/soko2.in");
    my_map *L3 = loader("data/soko3.in");
    my_map *L4 = loader("data/soko4.in");

    printf(" | Test de enqueue (L1, 'N')...\n");
    enqueue(&queue, L1, 'N');
    printf(" | OK!\n");

    printf(" | Test de is_empty après un enqueue...\n");
    assert(!is_empty(queue));
    printf(" | OK!\n");

    printf(" | Test de size après un enqueue...\n");
    assert(size(queue) == 1);
    printf(" | OK!\n");

    printf(" | Test de queue->depth...\n");
    assert(queue->depth == 0);
    printf(" | OK!\n");

    printf(" | Test de queue->map...\n");
    assert(queue->map == L1);
    printf(" | OK!\n");

    enqueue(&queue, L2, 'S');
    enqueue(&queue, L3, 'E');
    enqueue(&queue, L4, 'W');
    printf(" | Test de size après 4 enqueue...\n");
    assert(size(queue) == 4);
    printf(" | OK!\n");

    linked_list_queue q_L1 = get_element(queue, 0);
    assert(q_L1->map == L1);
    assert(q_L1->action == 'N');
    assert(q_L1->depth == 0);
    printf(" | OK!\n");

    linked_list_queue q_L4 = get_element(queue, 3);
    assert(q_L4->map == L4);
    assert(q_L4->action == 'W');
    assert(q_L4->depth == 3);
    printf(" | OK!\n");

    printf(" | Test de dequeue (retire L1)...\n");
    cell_queue *removed = dequeue(&queue);
    assert(removed->map == L1);
    free(removed);
    assert(size(queue) == 3);
    printf(" | OK!\n");

    dequeue(&queue);  // retire L2
    dequeue(&queue);  // retire L3
    dequeue(&queue);  // retire L4
    assert(is_empty(queue));
    printf(" | OK!\n");

    printf(" | Test de deallocate_list sur file vide...\n");
    deallocate_list(queue);  // sécuritaire même si NULL
    printf(" | OK!\n");

    printf(" | Tous les tests se sont terminés avec succès !\n");
    return 0;
}
