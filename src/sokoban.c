#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sokoban.h"

// function of the 5.1

void print_map(my_map *MY_MAP)

{

    int hauteur = MY_MAP->height ;
    int largeur = MY_MAP->width ;
    int positionh = MY_MAP->hposition ;
    int positionv = MY_MAP->vposition ;
    char *MAP = MY_MAP->map ;

    printf("position_h = %d et position_v = %d", positionh, positionv);
    printf("\n");

    for (int j = 0 ; j < hauteur ; j++)

    {
    
        for (int i = 0 ; i < largeur ; i++)
    
        {
            printf("%c", MAP[j*largeur + i]);
        }

        printf("\n");
    
    }

}

// function of the 5.3

my_map *move(char direction, my_map * p_map)

{   

    int height = p_map->height;
    int width = p_map->width;
    int hposition = p_map->hposition;
    int vposition = p_map->vposition;

    // creating the result

    my_map *result = malloc(sizeof(my_map)); 
    my_map *output = malloc(sizeof(my_map));

    // if the player can't move
    
    output->width = width;
    output->height = height;
    output->hposition = hposition;
    output->vposition = vposition;

    result->width = width;
    result->height = height;

    char *new_map = malloc(sizeof(char[width*height]));
    
    output->map = p_map->map;

    for (int k = 0 ; k < width*height ; k++)

    {
        new_map[k] = p_map->map[k];
        output->map[k]=p_map->map[k];
    }

    if (direction == 'N')

    {
        if ((p_map->map[(vposition - 1)*width + hposition]) == '*' || 
            (p_map->map[(vposition - 1)*width + hposition]) == '#')

        {
            return output;
        }

        else if ((p_map->map[(vposition - 1)*width + hposition]) == ' ' ||
                 (p_map->map[(vposition - 1)*width + hposition]) == '.')
        
        {
                    new_map[(vposition - 1)*width + hposition] = '@' ;
                    new_map[(vposition)*width + hposition] = ' ' ; 
                    
                    result->map = new_map ;
                    result->hposition = hposition ;
                    result->vposition = vposition + 1 ;
                    return result;         
        }

        else if ((p_map->map[(vposition - 1)*width + hposition]) == '$')

        {
            if ((p_map->map[(vposition - 2)*width + hposition]) == '*' || 
                (p_map->map[(vposition - 2)*width + hposition]) == '#')

                {
                    return output;
                }

        }
    }

    else if (direction == 'S')

    {
        if ((p_map->map[(vposition + 1)*width + hposition]) == '*' || 
            (p_map->map[(vposition + 1)*width + hposition]) == '#')

        {
            return output;
        }
        else if ((p_map->map[(vposition + 1)*width + hposition]) == ' ' ||
                 (p_map->map[(vposition + 1)*width + hposition]) == '.')

        {
                    new_map[(vposition + 1)*width + hposition] = '@' ;
                    new_map[(vposition)*width + hposition] = ' ' ; 
                    
                    result->map = new_map ;
                    result->hposition = hposition ;
                    result->vposition = vposition - 1 ;
                    return result;         
        }

        else if ((p_map->map[(vposition + 1)*width + hposition]) == '$')

        {
            if ((p_map->map[(vposition + 2)*width + hposition]) == '*' || 
                (p_map->map[(vposition + 2)*width + hposition]) == '#')

                {
                    return output;
                }

        }
        
    }

    else if (direction == 'O')

    {
        if ((p_map->map[vposition*width + hposition - 1]) == '*' || 
            (p_map->map[vposition*width + hposition - 1]) == '#')

        {
            return output;
        }

        else if ((p_map->map[vposition*width + hposition - 1]) == ' ' ||
                 (p_map->map[vposition*width + hposition - 1]) == '.')

        {
                    new_map[vposition*width + hposition - 1] = '@' ;
                    new_map[vposition*width + hposition] = ' ' ;
                    result->map = new_map ;
                    result->hposition = hposition - 1 ;
                    result->vposition = vposition ; 
                    return result;         
        }

        else if ((p_map->map[vposition*width + hposition - 1]) == '$')

        {
            if ((p_map->map[vposition*width + hposition - 2]) == '*' || 
                (p_map->map[vposition*width + hposition - 2]) == '#')
                {
                    return output;
                }
        }

    }

    else if (direction == 'E')

    {
        if ((p_map->map[vposition*width + hposition + 1]) == '*' || 
            (p_map->map[vposition*width + hposition + 1]) == '#')

        {
            return output;
        }

        else if ((p_map->map[vposition*width + hposition + 1]) == ' ' ||
                 (p_map->map[vposition*width + hposition + 1]) == '.')

        {
                    new_map[vposition*width + hposition + 1] = '@' ;
                    new_map[vposition*width + hposition] = ' ' ; 
                    result->map = new_map ; 
                    result->hposition = hposition + 1 ;
                    result->vposition = vposition ;
                    return result;         
        }

        else if ((p_map->map[vposition*width + hposition + 1]) == '$')

        {
            if ((p_map->map[vposition*width + hposition + 2]) == '*' || 
                (p_map->map[vposition*width + hposition + 2]) == '#')

                {
                    return output ;
                }

        } 

    }

    else

    {
        printf("problème") ;
        return result ;
    }

    return result ;

    free(output);
    free(result);
    free(new_map);

}

// needed function for test-move
// function comparing two my_map struct
// function returning 1 or 0

int struct_comparison(my_map * map_1, my_map * map_2)

{

    int height1 = map_1->height ;
    int width1 = map_1->width ;
    char * map1 = map_1->map ;
    int x_1 = map_1->hposition ; 
    int y_1 = map_1->vposition ; 

    int height2 = map_2->height ;
    int width2 = map_2->width ;
    char * map2 = map_2->map ;
    int x_2 = map_2->hposition ; 
    int y_2 = map_2->vposition ; 

    if(height1 != height2 || width1 != width2 || x_1 != x_2 || y_1 != y_2)
    
    {
    
        return 0;
    
    }

    else

    {

        for(int k = 0 ; k < height1 * width1 ; k++)
    
        {
            if (map1[k] != map2[k])

            {
                return 0;
            }

        }
    
    }

    return 1;

}

// function of the 5.4

my_map * replay(struct my_map * map_arg, int L, char * moves)

{
    my_map *map_replay = malloc(sizeof(my_map)); 

    for (int k = 0 ; k < L ; k++)

    {
        map_arg->map[k] = move(moves[k], map_arg)->map[k]; 
    }

    int H = map_arg->height;
    int W = map_arg->width;
    int HP = map_arg->hposition;
    int VP = map_arg->hposition;

    map_replay->height = H;
    map_replay->width = W;
    map_replay->hposition = HP;
    map_replay->vposition = VP;

    return map_replay;

    free(map_replay);

}