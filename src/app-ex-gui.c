#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <SDL2/SDL.h>
#include "gui.h"

#define MAX_LEVELS 100
#define LEVEL_DIR "data"

void print_terminal_map(int width, int height, char *level) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printf("%c", level[i * width + j]);
        }
        printf("\n");
    }
}

void go_dir(int width, int height, char *level, int dx, int dy, int *p_x, int *p_y) {
    int x = *p_x;
    int y = *p_y;
    int nx = x + dx;
    int ny = y + dy;
    int nnx = x + 2*dx;
    int nny = y + 2*dy;

    // Vérifier que la destination est dans la map
    if (nx < 0 || ny < 0 || nx >= width || ny >= height)
        return;

    char dest = level[ny * width + nx];
    char behind = (nnx >= 0 && nnx < width && nny >= 0 && nny < height) ? level[nny * width + nnx] : '#';

    if (dest == '#')
        return; // Mur => impossible

    // Pousser une boîte
    if (dest == '$' || dest == '*') {
        if (behind == ' ' || behind == '.') {
            level[nny * width + nnx] = (behind == '.') ? '*' : '$';
            level[ny * width + nx] = (dest == '*') ? '.' : ' ';
        } else {
            return; // Impossible de pousser
        }
    } else if (!(dest == ' ' || dest == '.' || dest == '+')) {
        return; // Blocage
    }

    // Effacer ancienne position
    if (level[y * width + x] == '@')
        level[y * width + x] = ' ';
    else if (level[y * width + x] == '+')
        level[y * width + x] = '.';

    // Déplacer joueur
    if (dest == '.' || dest == '*')
        level[ny * width + nx] = '+';
    else
        level[ny * width + nx] = '@';

    *p_x = nx;
    *p_y = ny;
}


bool check_victory(int width, int height, char *level) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (level[y * width + x] == '.') return false;
        }
    }
    return true;
}

int load_level(const char *filename, int *width, int *height, char **level, int *x, int *y) {
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
        if (fgets(buffer, sizeof buffer, file) == NULL) break;
        for (int j = 0; j < *width && buffer[j] != '\0' && buffer[j] != '\n' && buffer[j] != '\r'; j++) {
            (*level)[i * (*width) + j] = buffer[j];
            if (buffer[j] == '@' || buffer[j] == '+') {
                *x = j;
                *y = i;
            }
        }
    }

    fclose(file);
    return 1;
}

int compare_str(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

int main() {
    DIR *dir;
    struct dirent *entry;
    char *levels[MAX_LEVELS];
    int level_count = 0;

    dir = opendir(LEVEL_DIR);
    if (!dir) {
        perror("Impossible d'ouvrir le dossier de niveaux");
        return EXIT_FAILURE;
    }

    while ((entry = readdir(dir)) != NULL && level_count < MAX_LEVELS) {
        if (strstr(entry->d_name, ".in")) {
            levels[level_count] = malloc(strlen(LEVEL_DIR) + strlen(entry->d_name) + 2);
            sprintf(levels[level_count], "%s/%s", LEVEL_DIR, entry->d_name);
            level_count++;
        }
    }
    closedir(dir);

    if (level_count == 0) {
        fprintf(stderr, "Aucun niveau trouvé dans '%s'\n", LEVEL_DIR);
        return EXIT_FAILURE;
    }

    qsort(levels, level_count, sizeof(char *), compare_str);

    for (int current = 0; current < level_count; current++) {
        int width, height, x = 0, y = 0;
        char *level = NULL;

        if (!load_level(levels[current], &width, &height, &level, &x, &y)) {
            fprintf(stderr, "Erreur chargement niveau : %s\n", levels[current]);
            continue;
        }

        printf("\n=== Niveau %d : %s ===\n", current + 1, levels[current]);
        print_terminal_map(width, height, level);  // Affichage dans le terminal

        GUI_init("Sokoban", width, height);
        GUI_show(width, height, level);

        bool stop = false;
        while (!stop) {
            int key = GUI_get_key();  // SDL, pas getchar() !
        
            switch (key) {
                case SDLK_UP:    go_dir(width, height, level, 0, -1, &x, &y); break;
                case SDLK_DOWN:  go_dir(width, height, level, 0, 1, &x, &y); break;
                case SDLK_LEFT:  go_dir(width, height, level, -1, 0, &x, &y); break;
                case SDLK_RIGHT: go_dir(width, height, level, 1, 0, &x, &y); break;
                case 'q': stop = true; current = level_count; break;
                case 'n': stop = true; break;
                case -1:  stop = true; break;
            }
        
            GUI_show(width, height, level);  // rafraîchir la fenêtre SDL
        
            if (check_victory(width, height, level)) {
                printf("\n>>> Victoire !\n");
                GUI_pause(1500);
                stop = true;
            }
        }
        

        print_terminal_map(width, height, level);
        GUI_show(width, height, level);

        if (check_victory(width, height, level)) {
            printf("\n>>> Victoire !\n");
            GUI_pause(1500);
            stop = true;
        }
        

        free(level);
        GUI_close();
    }

    for (int i = 0; i < level_count; i++) {
        free(levels[i]);
    }

    printf("\nTous les niveaux ont été joués. Merci !\n");
    return EXIT_SUCCESS;
}
