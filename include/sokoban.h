#include <stdio.h>
#include <stdlib.h>

struct my_map

{
    //height of the structure
    int height;
    //width of the structure
    int width;
    //horizontal position of the player
    int hposition;
    //vertical position of the player
    int vposition;
    // elements of the map
    char * map;
};

typedef struct my_map my_map;

void print_map(struct my_map *MY_MAP);

/**
 * @brief Prints the map represented by the structure my_map
 *
 * @param MY_MAP a pointer to a structure representing the map that we want to print
 */


my_map * move(char direction, struct my_map *p_map);

/**
 * @brief Moves the player if it is possible
 *
 * Returns the final map if the player can move, the initial move if he can't
 *
 * @param direction a char representing the direction in which we want to move the player
 *
 * @param p_map a pointer to a structure representing the initial map
 */


int struct_comparison(my_map *map_1, my_map *map_2);

/**
 * @brief Compare two structures of map

 * Returns 1 if they are similar, 0 if not
 *
 * @param map_1 a pointer to a stucture representing the first map
 *
 * @param map_2 a pointer to a stucture representing the second map
*/


char * modify_lines(char *line_not_modified);

/**
 * @brief Modify the way the char is written

 * Returns the *char modified, represented under several lines
 *
 * @param line_not_modified a *char represented by one only line
 */


// the struct returned by the replay function

typedef struct my_map map_replay;

my_map * replay(struct my_map *map_arg, int L, char *moves);

/**
 * @brief replay

 * Returns the *my_map modified, once the moves are done
 *
 * @param map_arg a pointer to a structure representing the initial map
 *
 * @param L an int representing the number of moves we want to do
 * 
 * @param moves a *char representing the potential sequence of moves we can do
 */