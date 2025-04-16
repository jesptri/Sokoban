#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <SDL2/SDL.h>
#include "gui.h"

#define MAX_WIDTH 100
#define MAX_HEIGHT 100
#define MAX_LEVELS 100
#define LEVEL_DIR "data"

void go_dir(int width, int height, char level[height][width], int dx, int dy, int *p_x, int *p_y) {
    int x = *p_x;
    int y = *p_y;
    int nx = x + dx;
    int ny = y + dy;
    int nnx = x + 2*dx;
    int nny = y + 2*dy;

    char dest = level[ny][nx];
    char behind = (nnx >= 0 && nnx < width && nny >= 0 && nny < height) ? level[nny][nnx] : '#';

    if (dest == '#') return;

    if (dest == '$' || dest == '*') {
        if (behind == ' ' || behind == '.') {
            level[nny][nnx] = (behind == '.') ? '*' : '$';
            level[ny][nx] = (dest == '*') ? '.' : ' ';
        } else {
            return;
        }
    } else if (dest != ' ' && dest != '.') {
        return;
    }

    level[y][x] = (level[y][x] == '@' && level[y][x] != '*') ? ' ' : '.';
    level[ny][nx] = (dest == '.') ? '@' : '@';
    *p_x = nx;
    *p_y = ny;
}

bool check_victory(int width, int height, char level[height][width]) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (level[y][x] == '.') return false;
        }
    }
    return true;
}

int load_level(const char *filename, int *width, int *height, char level[MAX_HEIGHT][MAX_WIDTH], int *x, int *y) {
    FILE *file = fopen(filename, "r");
    if (!file) return 0;

    if (fscanf(file, "%d %d\n", width, height) != 2 || *width > MAX_WIDTH || *height > MAX_HEIGHT) {
        fclose(file);
        return 0;
    }

    memset(level, ' ', MAX_HEIGHT * MAX_WIDTH);
    char buffer[MAX_WIDTH + 2];
    for (int i = 0; i < *height; i++) {
        if (fgets(buffer, sizeof buffer, file) == NULL) break;
        for (int j = 0; j < *width && buffer[j] != '\0' && buffer[j] != '\n'; j++) {
            level[i][j] = buffer[j];
            if (buffer[j] == '@') {
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
        int width, height, x, y;
        char level[MAX_HEIGHT][MAX_WIDTH];

        if (!load_level(levels[current], &width, &height, level, &x, &y)) {
            fprintf(stderr, "Erreur chargement niveau : %s\n", levels[current]);
            continue;
        }

        level[y][x] = '@';

        printf("\n=== Niveau %d : %s ===\n", current + 1, levels[current]);
        GUI_init("Sokoban", width, height);
        GUI_show(width, height, level);

        bool stop = false;
        while (!stop) {
            int key = GUI_get_key();

            switch (key) {
                case SDLK_UP: go_dir(width, height, level, 0, -1, &x, &y); break;
                case SDLK_DOWN: go_dir(width, height, level, 0, 1, &x, &y); break;
                case SDLK_LEFT: go_dir(width, height, level, -1, 0, &x, &y); break;
                case SDLK_RIGHT: go_dir(width, height, level, 1, 0, &x, &y); break;
                case 'q': stop = true; current = level_count; break;
                case 'n': stop = true; break;
                case -1: stop = true; break;
            }

            GUI_show(width, height, level);

            if (check_victory(width, height, level)) {
                printf("\n>>> Victoire !\n");
                GUI_pause(1500);
                stop = true;
            }
        }
        GUI_close();
    }

    for (int i = 0; i < level_count; i++) {
        free(levels[i]);
    }

    printf("\nTous les niveaux ont été joués. Merci !\n");
    return EXIT_SUCCESS;
}