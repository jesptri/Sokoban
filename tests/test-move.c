#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "sokoban.h"
#include "loader.h"

int main(void) {

  printf(" | Simple player movements: \n");

  // --- Exemple 1 ---

  my_map *initial_map_1 = loader("data/soko_move_1.in");

  printf(" | Move to South...");
  my_map *final_map_1_S = loader("data/soko_move_1_S.in");
  my_map *moved_map_1_S = move('S', initial_map_1);
  assert(strcmp(final_map_1_S->map, moved_map_1_S->map) == 0);
  printf(" | OK!\n");
  free(final_map_1_S->map); free(final_map_1_S);
  free(moved_map_1_S->map); free(moved_map_1_S);

  printf(" | Move to North...");
  my_map *final_map_1_N = loader("data/soko_move_1_N.in");
  my_map *moved_map_1_N = move('N', initial_map_1);
  assert(strcmp(final_map_1_N->map, moved_map_1_N->map) == 0);
  printf(" | OK!\n");
  free(final_map_1_N->map); free(final_map_1_N);
  free(moved_map_1_N->map); free(moved_map_1_N);

  printf(" | Move to East...");
  my_map *final_map_1_E = loader("data/soko_move_1_E.in");
  my_map *moved_map_1_E = move('E', initial_map_1);
  assert(strcmp(final_map_1_E->map, moved_map_1_E->map) == 0);
  printf(" | OK!\n");
  free(final_map_1_E->map); free(final_map_1_E);
  free(moved_map_1_E->map); free(moved_map_1_E);

  printf(" | Move to West...");
  my_map *final_map_1_W = loader("data/soko_move_1_W.in");
  my_map *moved_map_1_W = move('W', initial_map_1);
  assert(strcmp(final_map_1_W->map, moved_map_1_W->map) == 0);
  printf(" | OK!\n");
  free(final_map_1_W->map); free(final_map_1_W);
  free(moved_map_1_W->map); free(moved_map_1_W);

  free(initial_map_1->map); free(initial_map_1);

  // --- Exemple 2 ---

  my_map *initial_map_2 = loader("data/soko_move_2.in");

  printf(" | Move to East...");
  my_map *final_map_2_E = loader("data/soko_move_2_E.in");
  my_map *moved_map_2_E = move('E', initial_map_2);
  assert(strcmp(final_map_2_E->map, moved_map_2_E->map) == 0);
  printf(" | OK!\n");
  free(final_map_2_E->map); free(final_map_2_E);
  free(moved_map_2_E->map); free(moved_map_2_E);

  printf(" | Move to South...");
  my_map *final_map_2_S = loader("data/soko_move_2_S.in");
  my_map *moved_map_2_S = move('S', initial_map_2);
  assert(strcmp(final_map_2_S->map, moved_map_2_S->map) == 0);
  printf(" | OK!\n");
  free(final_map_2_S->map); free(final_map_2_S);
  free(moved_map_2_S->map); free(moved_map_2_S);

  printf(" | Move to West...");
  my_map *final_map_2_W = loader("data/soko_move_2_W.in");
  my_map *moved_map_2_W = move('W', initial_map_2);
  assert(strcmp(final_map_2_W->map, moved_map_2_W->map) == 0);
  printf(" | OK!\n");
  free(final_map_2_W->map); free(final_map_2_W);
  free(moved_map_2_W->map); free(moved_map_2_W);

  printf(" | Move to North...");
  my_map *final_map_2_N = loader("data/soko_move_2_N.in");
  my_map *moved_map_2_N = move('N', initial_map_2);
  assert(strcmp(final_map_2_N->map, moved_map_2_N->map) == 0);
  printf(" | OK!\n");
  free(final_map_2_N->map); free(final_map_2_N);
  free(moved_map_2_N->map); free(moved_map_2_N);
  free(initial_map_2->map); free(initial_map_2);

  // --- Move box cases ---

  // 3.1 - East
  my_map *initial_map_3_1 = loader("data/soko_move_3_1.in");
  my_map *final_map_3_1_E = loader("data/soko_move_3_1_E.in");
  my_map *moved_map_3_1_E = move('E', initial_map_3_1);
  assert(strcmp(final_map_3_1_E->map, moved_map_3_1_E->map) == 0);
  printf(" | Move box to East... OK!\n");
  free(final_map_3_1_E->map); free(final_map_3_1_E);
  free(moved_map_3_1_E->map); free(moved_map_3_1_E);
  free(initial_map_3_1->map); free(initial_map_3_1);

  // 4.1 - West
  my_map *initial_map_4_1 = loader("data/soko_move_4_1.in");
  my_map *final_map_4_1_W = loader("data/soko_move_4_1_W.in");
  my_map *moved_map_4_1_W = move('W', initial_map_4_1);
  assert(strcmp(final_map_4_1_W->map, moved_map_4_1_W->map) == 0);
  printf(" | Move box to West... OK!\n");
  free(final_map_4_1_W->map); free(final_map_4_1_W);
  free(moved_map_4_1_W->map); free(moved_map_4_1_W);
  free(initial_map_4_1->map); free(initial_map_4_1);

  // 5.1 - North
  my_map *initial_map_5_1 = loader("data/soko_move_5_1.in");
  my_map *final_map_5_1_N = loader("data/soko_move_5_1_N.in");
  my_map *moved_map_5_1_N = move('N', initial_map_5_1);
  assert(strcmp(final_map_5_1_N->map, moved_map_5_1_N->map) == 0);
  printf(" | Move box to North... OK!\n");
  free(final_map_5_1_N->map); free(final_map_5_1_N);
  free(moved_map_5_1_N->map); free(moved_map_5_1_N);
  free(initial_map_5_1->map); free(initial_map_5_1);

  // 6.1 - South
  my_map *initial_map_6_1 = loader("data/soko_move_6_1.in");
  my_map *final_map_6_1_S = loader("data/soko_move_6_1_S.in");
  my_map *moved_map_6_1_S = move('S', initial_map_6_1);
  assert(strcmp(final_map_6_1_S->map, moved_map_6_1_S->map) == 0);
  printf(" | Move box to South... OK!\n");
  free(final_map_6_1_S->map); free(final_map_6_1_S);
  free(moved_map_6_1_S->map); free(moved_map_6_1_S);
  free(initial_map_6_1->map); free(initial_map_6_1);

  // 6.2 - South
  my_map *initial_map_6_2 = loader("data/soko_move_6_2.in");
  my_map *final_map_6_2_S = loader("data/soko_move_6_2_S.in");
  my_map *moved_map_6_2_S = move('S', initial_map_6_2);
  assert(strcmp(final_map_6_2_S->map, moved_map_6_2_S->map) == 0);
  printf(" | Move box to South (6.2)... OK!\n");
  free(final_map_6_2_S->map); free(final_map_6_2_S);
  free(moved_map_6_2_S->map); free(moved_map_6_2_S);
  free(initial_map_6_2->map); free(initial_map_6_2);

  // --- Nothing happens cases ---

  my_map *map_nothing_E = loader("data/soko_move_W_E.in");
  my_map *result_nothing_E = move('E', map_nothing_E);
  assert(strcmp(map_nothing_E->map, result_nothing_E->map) == 0);
  printf(" | Nothing happens (East)... OK!\n");
  free(map_nothing_E->map); 
  free(map_nothing_E);

  my_map *map_nothing_W = loader("data/soko_move_W_W.in");
  my_map *result_nothing_W = move('W', map_nothing_W);
  assert(strcmp(map_nothing_W->map, result_nothing_W->map) == 0);
  printf(" | Nothing happens (West)... OK!\n");
  free(map_nothing_W->map); 
  free(map_nothing_W);

  my_map *map_nothing_N = loader("data/soko_move_W_N.in");
  my_map *result_nothing_N = move('N', map_nothing_N);
  assert(strcmp(map_nothing_N->map, result_nothing_N->map) == 0);
  printf(" | Nothing happens (North)... OK!\n");
  free(map_nothing_N->map); 
  free(map_nothing_N);

  my_map *map_nothing_S = loader("data/soko_move_W_S.in");
  my_map *result_nothing_S = move('S', map_nothing_S);
  assert(strcmp(map_nothing_S->map, result_nothing_S->map) == 0);
  printf(" | Nothing happens (South)... OK!\n");
  free(map_nothing_S->map); 
  free(map_nothing_S);

  my_map *map_box_blocked_E = loader("data/soko_move_B_W_E.in");
  my_map *result_box_blocked_E = move('E', map_box_blocked_E);
  assert(strcmp(map_box_blocked_E->map, result_box_blocked_E->map) == 0);
  printf(" | Box blocked (East)... OK!\n");
  free(map_box_blocked_E->map); 
  free(map_box_blocked_E);

  return 0;
}
