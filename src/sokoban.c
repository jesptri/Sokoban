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

    printf("position_h = %d and position_v = %d", positionh, positionv);
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

my_map *move(char direction, my_map *p_map) {
    int height = p_map->height;
    int width = p_map->width;
    int h = p_map->hposition;
    int v = p_map->vposition;

    my_map *result = malloc(sizeof(my_map));
    result->width = width;
    result->height = height;

    char *new_map = malloc(sizeof(char) * width * height);
    for (int k = 0; k < width * height; k++) {
        new_map[k] = p_map->map[k];
    }

    // Définir les décalages selon la direction
    int dh = 0, dv = 0;
    if (direction == 'N') dv = -1;
    else if (direction == 'S') dv = 1;
    else if (direction == 'W') dh = -1;
    else if (direction == 'E') dh = 1;

    int current = v * width + h;
    int next = (v + dv) * width + (h + dh);
    int next2 = (v + 2 * dv) * width + (h + 2 * dh);

    char cur_char = p_map->map[current];
    char next_char = p_map->map[next];
    char next2_char = p_map->map[next2];

    // Fonction utilitaire pour mettre à jour la case du joueur actuel
    void clear_current() {
        if (cur_char == '+')
            new_map[current] = '.';
        else
            new_map[current] = ' ';
    }

    // Si mur => bloqué
    if (next_char == '#') {
        free(new_map);
        free(result);
        return p_map;
    }

    // Si case vide
    if (next_char == ' ') {
        clear_current();
        new_map[next] = '@';
    }

    // Si cible
    else if (next_char == '.') {
        clear_current();
        new_map[next] = '+';
    }

    // Si caisse simple
    else if (next_char == '$') {
        if (next2_char == ' ' || next2_char == '.') {
            clear_current();
            new_map[next] = '@';
            new_map[next2] = (next2_char == '.') ? '*' : '$';
        } else {
            free(new_map);
            free(result);
            return p_map;
        }
    }

    // Si caisse sur cible
    else if (next_char == '*') {
        if (next2_char == ' ' || next2_char == '.') {
            clear_current();
            new_map[next] = '+';
            new_map[next2] = (next2_char == '.') ? '*' : '$';
        } else {
            free(new_map);
            free(result);
            return p_map;
        }
    }

    // Si rien de prévu, retour à l'identique
    else {
        free(new_map);
        free(result);
        return p_map;
    }

    result->map = new_map;
    result->hposition = h + dh;
    result->vposition = v + dv;
    return result;
}




int struct_comparison(my_map * map_1, my_map * map_2){

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

    if(height1 != height2 || width1 != width2 || x_1 != x_2 || y_1 != y_2){
        return 0;
    } else {
        for(int k = 0 ; k < height1 * width1 ; k++){
            if (map1[k] != map2[k]){
                return 0;
            }
        }
    }
    return 1;
}

// function of the 5.4

my_map * replay(my_map * map_arg, int L, char * moves){
    
    my_map * current = malloc(sizeof(my_map));  

    current->width = map_arg->width;
    current->height = map_arg->height;
    current->vposition = map_arg->vposition;
    current->hposition = map_arg->hposition;

    int size = map_arg->width * map_arg->height;

    current->map = malloc(size + 1);
    memcpy(current->map, map_arg->map, size);
    current->map[size] = '\0';

    for (int k = 0 ; k < L ; k++){
        my_map * next = move(moves[k], current);

        // free(current->map);
        // free(current);

        current = next;
    }

    return current;

}