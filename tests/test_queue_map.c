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

    // print_map(L1);
    // print_map(L2);
    // print_map(L3);
    // print_map(L4);

    printf(" | Test de enqueue (L1, 'N')...\n");
    queue = enqueue(queue, L1, 'N');
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

    printf(" | Test de enqueue (L2, 'S')...\n");
    queue = enqueue(queue, L2, 'S');
    printf(" | OK!\n");

    printf(" | Test de enqueue (L3, 'E')...\n");
    queue = enqueue(queue, L3, 'E');
    printf(" | OK!\n");

    printf(" | Test de enqueue (L4, 'W')...\n");
    queue = enqueue(queue, L4, 'W');
    printf(" | OK!\n");

    printf(" | Test de size après 4 enqueue...\n");
    assert(size(queue) == 4);
    printf(" | OK!\n");

    printf(" | Test de get_element position 0 (doit être L4)...\n");
    linked_list_queue q_L1 = get_element(queue, 0);
    print_map(q_L1->map);
    assert(q_L1->map == L1);
    assert(q_L1->action == 'N');
    assert(q_L1->depth == 0);
    printf(" | OK!\n");

    printf(" | Test de get_element position 3 (doit être L1)...\n");
    linked_list_queue q_L4 = get_element(queue, 3);
    assert(q_L4->map == L4);
    assert(q_L4->action == 'W');
    assert(q_L4->depth == 3);
    printf(" | OK!\n");

    printf(" | Test de dequeue (retire L1)...\n");
    queue = dequeue(queue);
    assert(size(queue) == 3);
    printf(" | OK!\n");

    printf(" | Test de dequeue (retire L2)...\n");
    queue = dequeue(queue);
    assert(size(queue) == 2);
    printf(" | OK!\n");

    printf(" | Test de dequeue (retire L3)...\n");
    queue = dequeue(queue);
    assert(size(queue) == 1);
    printf(" | OK!\n");

    printf(" | Test de dequeue (retire L4)...\n");
    queue = dequeue(queue);
    assert(is_empty(queue));
    assert(size(queue) == 0);
    printf(" | OK!\n");

    printf(" | Test de deallocate_list sur file vide...\n");
    deallocate_list(queue);  // NULL-safe
    printf(" | OK!\n");

    printf(" | Tous les tests se sont terminés avec succès !\n");
    return 0;
}
