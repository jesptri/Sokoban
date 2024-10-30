#include <stdio.h>
#include <stdlib.h>

typedef struct my_map my_map;

my_map * loader(char *file_adress);

/**
 * @brief Returns a pointer to a struct reprensenting the map represented in the file
 *
 * @param file_adress a char* representing the adress of the file
 */
