#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "sokoban.h"
#include "loader.h"

int main(void)

{

  printf(" | First test...\n");

  // creating the different maps to compare them

  // first example

  my_map *final_map = malloc(sizeof(my_map));

  final_map = loader("data/soko_move_1_S.in");
  printf(final_map);

  my_map *moved_map = malloc(sizeof(my_map));

  moved_map = move('S', loader("data/soko_move_1.in"));

  // printf("%s\n", final_map->map);
  // printf("%s\n", moved_map->map);

  printf(" | OK!\n");

  free(final_map);
  free(moved_map);

  // second example

  printf(" | Second test...\n");

  my_map *final_map_2 = malloc(sizeof(my_map));

  final_map_2 = loader("data/soko_move_1_E.in");

  my_map *moved_map_2 = malloc(sizeof(my_map));

  moved_map_2 = move('E', loader("data/soko_move_1.in"));

  printf("%s\n", final_map_2->map);
  printf("%s\n", moved_map_2->map);

  printf(" | OK!\n");

  free(final_map_2);
  free(moved_map_2);

  // third example

  printf(" | Third test...\n");

  my_map *final_map_3 = malloc(sizeof(my_map));

  final_map_3 = loader("data/soko_move_1_W.in");

  my_map *moved_map_3 = malloc(sizeof(my_map));

  moved_map_3 = move('O', loader("data/soko_move_1.in"));

  printf("%s\n", final_map_3->map);
  printf("%s\n", moved_map_3->map);

  printf(" | OK!\n");

  free(final_map_3);
  free(moved_map_3);

  return 0;
  
}