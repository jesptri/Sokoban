#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "loader.h"
#include "sokoban.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s fichier_niveau.in commandes\n", argv[0]);
        return EXIT_FAILURE;
    }

    int width, height, x = 0, y = 0;
    char *level = NULL;

    if (!load_level(argv[1], &width, &height, &level, &x, &y)) {
        fprintf(stderr, "Erreur chargement niveau : %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    char *commands = argv[2];

    for (int i = 0; commands[i] != '\0'; i++) {
        switch (commands[i]) {
            case 'n': go_dir(width, height, level, 0, -1, &x, &y); break;
            case 's': go_dir(width, height, level, 0, 1, &x, &y); break;
            case 'w': go_dir(width, height, level, -1, 0, &x, &y); break;
            case 'e': go_dir(width, height, level, 1, 0, &x, &y); break;
        }
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printf("%c", level[i * width + j]);
        }
        printf("\n");
    }

    if (check_victory(width, height, level)) {
        printf("Won!");
    } else {
        printf("Not won...");
    }

    free(level);
    return EXIT_SUCCESS;
}
