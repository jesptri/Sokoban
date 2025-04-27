#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sokoban.h"
#include "loader.h"

my_map * loader(char *file_adress) 

{

    // creating the result

    my_map * result = (my_map*)malloc(sizeof(my_map));

    // filling the dynamicaly allocated structure

    // open file. The filename is the first argument on the command
    // line, hence stored in argv[1]
    FILE * p_file = NULL;

    p_file = fopen(file_adress, "r");

    if (p_file == NULL)
    
    {
        fprintf(stderr, "Cannot read file %s!\n", file_adress);
        exit(EXIT_FAILURE);
    }

    // read dimensions on first line

    int width         = 0;
    int height        = 0;
    int fscanf_result = 0;

    fscanf_result = fscanf(p_file, "%d %d\n", &width, &height);

    if (fscanf_result != 2) 

    {
        fprintf(stderr, "First line is not syntactically correct!\n");
        exit(EXIT_FAILURE);
    }

    result->width = width;
    result->height = height;

    //reading the string representing the map 

    char * p_string_map = (char *)malloc(width*height*sizeof(char));

    // read following lines
    // line_buffer contains a line and is a correct string
    // width + 2 is needed to get the carriage return symbol

    char line_buffer[width + 2];

    for (int i = 0; i < height; i++) 

    {
        fgets(line_buffer, width + 2, p_file);
        for (int row_ind = 0; row_ind < width; row_ind++)

        {
            p_string_map[row_ind + i*width] = line_buffer[row_ind];
        }

    }

    result->map = p_string_map;

    fclose(p_file);

    //finding the player position
    for (int x =0; x < width; x++)

    {
        for (int y = 0; y < height; y++)

        {
            if (p_string_map[ x + y*width] == '@' || p_string_map[x +y*width]=='+')

            {
                result->hposition = x;
                result->vposition = y;
            }

        }
        
    }

    return result;
    
}

int load_level(const char *filename, int *width, int *height, char **level, int *p_x, int *p_y) {
    FILE *file = fopen(filename, "r");
    if (!file) return 0;

    if (fscanf(file, "%d %d\n", width, height) != 2) {
        fclose(file);
        return 0;
    }

    *level = malloc((*width) * (*height) * sizeof(char));
    if (!*level) {
        fclose(file);
        return 0;
    }

    // Initialiser avec des espaces
    for (int i = 0; i < (*width) * (*height); i++) {
        (*level)[i] = ' ';
    }

    char buffer[256];
    for (int i = 0; i < *height; i++) {
        if (fgets(buffer, sizeof(buffer), file) == NULL) break;
        for (int j = 0; j < *width && buffer[j] != '\0' && buffer[j] != '\n' && buffer[j] != '\r'; j++) {
            (*level)[i * (*width) + j] = buffer[j];
            if (buffer[j] == '@' || buffer[j] == '+') {
                *p_x = j;
                *p_y = i;
            }
        }
    }

    fclose(file);
    return 1;
}
