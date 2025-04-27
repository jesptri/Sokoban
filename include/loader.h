#include <stdio.h>
#include <stdlib.h>

typedef struct my_map my_map;

my_map * loader(char *file_adress);

/**
 * @brief Returns a pointer to a struct reprensenting the map represented in the file
 *
 * @param file_adress a char* representing the adress of the file
 */

 #ifndef LOADER_H
 #define LOADER_H
 
 int load_level(const char *filename, int *width, int *height, char **level, int *p_x, int *p_y);
 
 #endif

