#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sokoban.h"

// function of the 5.1

void print_map(my_map *MY_MAP){

    int hauteur = MY_MAP->height ;
    int largeur = MY_MAP->width ;
    int positionh = MY_MAP->hposition ;
    int positionv = MY_MAP->vposition ;
    char *MAP = MY_MAP->map ;

    printf("position_h = %d and position_v = %d", positionh, positionv);
    printf("\n");

    for (int j = 0 ; j < hauteur ; j++){
    
        for (int i = 0 ; i < largeur ; i++){
            printf("%c", MAP[j*largeur + i]);
        }

        printf("\n");
    
    }

}

// Fonction utilitaire pour mettre à jour la case du joueur actuel
void clear_current(char *new_map, int current, char cur_char) {
    if (cur_char == '+')
        new_map[current] = '.';
    else
        new_map[current] = ' ';
}

// function of the 5.3

my_map *move(char direction, my_map *p_map){

    int height = p_map->height;
    int width = p_map->width;
    int h = p_map->hposition;
    int v = p_map->vposition;

    // Définir les décalages selon la direction
    int dh = 0, dv = 0;
    if (direction == 'N') dv = -1;
    else if (direction == 'S') dv = 1;
    else if (direction == 'W') dh = -1;
    else if (direction == 'E') dh = 1;

    // Calcul des positions
    int current = v * width + h;
    int nh = h + dh;
    int nv = v + dv;
    int nh2 = h + 2 * dh;
    int nv2 = v + 2 * dv;

    // Vérifie que next et next2 sont dans les bornes de la grille
    if (nh < 0 || nh >= width || nv < 0 || nv >= height ||
        nh2 < 0 || nh2 >= width || nv2 < 0 || nv2 >= height) {
        return p_map;
    }

    int next = nv * width + nh;
    int next2 = nv2 * width + nh2;

    char cur_char = p_map->map[current];
    char next_char = p_map->map[next];
    char next2_char = p_map->map[next2];

    // Si mur => bloqué
    if (next_char == '#'){
        return NULL;
    }

    char *new_map = malloc(sizeof(char) * width * height+1);
    for (int k = 0; k < width * height; k++){
        new_map[k] = p_map->map[k];
    }

    if (next_char == ' '){
        clear_current(new_map, current, cur_char);
        new_map[next] = '@';
    }
    else if (next_char == '.'){
        clear_current(new_map, current, cur_char);
        new_map[next] = '+';
    }
    else if (next_char == '$'){
        if (next2_char == ' ' || next2_char == '.'){
        clear_current(new_map, current, cur_char);
            new_map[next] = '@';
            new_map[next2] = (next2_char == '.') ? '*' : '$';
        } else{
            free(new_map);
            return p_map;
        }
    }
    else if (next_char == '*'){
        if (next2_char == ' ' || next2_char == '.'){
        clear_current(new_map, current, cur_char);
            new_map[next] = '+';
            new_map[next2] = (next2_char == '.') ? '*' : '$';
        } else{
            free(new_map);
            return p_map;
        }
    }
    else{
        free(new_map);
        return p_map;
    }

    my_map *result = malloc(sizeof(my_map));

    result->width = width;
    result->height = height;
    result->map = new_map;
    result->hposition = h + dh;
    result->vposition = v + dv;

    return result;
}

void go_dir(int width, int height, char *level, int dx, int dy, int *p_x, int *p_y){
    int x = *p_x;
    int y = *p_y;
    int nx = x + dx;
    int ny = y + dy;
    int nnx = x + 2*dx;
    int nny = y + 2*dy;

    if (nx < 0 || ny < 0 || nx >= width || ny >= height) return;

    char dest = level[ny * width + nx];
    char behind = (nnx >= 0 && nnx < width && nny >= 0 && nny < height) ? level[nny * width + nnx] : '#';

    if (dest == '#') return;

    if (dest == '$' || dest == '*') {
        if (behind == ' ' || behind == '.') {
            level[nny * width + nnx] = (behind == '.') ? '*' : '$';
            level[ny * width + nx] = (dest == '*') ? '.' : ' ';
        } else {
            return;
        }
    } else if (!(dest == ' ' || dest == '.' || dest == '+')) {
        return;
    }

    if (level[y * width + x] == '@')
        level[y * width + x] = ' ';
    else if (level[y * width + x] == '+')
        level[y * width + x] = '.';

    if (dest == '.' || dest == '*')
        level[ny * width + nx] = '+';
    else
        level[ny * width + nx] = '@';

    *p_x = nx;
    *p_y = ny;
}

bool check_victory(int width, int height, char *level){
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (level[y * width + x] == '.') return false;
            if (level[y * width + x] == '$') return false;
            if (level[y * width + x] == '+') return false;
        }
    }
    return true;
}

// function of the 5.4

my_map *replay(my_map *map_arg, int L, char *moves){
    
    my_map *current = malloc(sizeof(my_map));  

    current->width = map_arg->width;
    current->height = map_arg->height;
    current->vposition = map_arg->vposition;
    current->hposition = map_arg->hposition;

    int size = map_arg->width * map_arg->height;

    current->map = malloc(size + 1);
    memcpy(current->map, map_arg->map, size);
    current->map[size] = '\0';

    for (int k = 0 ; k < L ; k++) {
        my_map *next = move(moves[k], current);

        if (next != current) {
            free(current->map);
            free(current);
        }

        current = next;
    }

    return current;

}