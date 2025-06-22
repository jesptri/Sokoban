#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <SDL2/SDL.h>

#include "gui.h"
#include "sokoban.h"
#include "loader.h"

#define MAX_LEVELS 100
#define LEVEL_DIR "data"

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

        GUI_init("Sokoban", width, height);
        GUI_show(width, height, level);

        bool stop = false;
        while (!stop) {
            int key = GUI_get_key();

            switch (key) {
                case SDLK_UP:    go_dir(width, height, level, 0, -1, &x, &y); break;
                case SDLK_DOWN:  go_dir(width, height, level, 0, 1, &x, &y); break;
                case SDLK_LEFT:  go_dir(width, height, level, -1, 0, &x, &y); break;
                case SDLK_RIGHT: go_dir(width, height, level, 1, 0, &x, &y); break;
                case 'q': stop = true; current = level_count; break;
                case 'n': stop = true; break;
                case -1:  stop = true; break;
            }

            GUI_show(width, height, level);

            if (check_victory(width, height, level)) {
                printf("\n>>> Victoire !\n");
                GUI_pause(1500);
                stop = true;
            }
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
