#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "loader.h"
#include "app-ex-gui.c"
#include "sokoban.h"

void print_terminal_map(int width, int height, char *level) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printf("%c", level[i * width + j]);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s fichier_niveau.in\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *filename = argv[1];
    int width, height, x = 0, y = 0;
    char *level = NULL;

    if (!load_level(filename, &width, &height, &level, &x, &y)) {
        fprintf(stderr, "Erreur chargement niveau : %s\n", filename);
        return EXIT_FAILURE;
    }

    bool stop = false;
    print_terminal_map(width, height, level);

    while (!stop) {
        printf("\nDéplacer (n/s/e/w) ou quitter (q) : ");
        int key = getchar();
        while (key == '\n') key = getchar(); // ignorer les retours à la ligne

        switch (key) {
            case 'n': go_dir(width, height, level, 0, -1, &x, &y); break;
            case 's': go_dir(width, height, level, 0, 1, &x, &y); break;
            case 'w': go_dir(width, height, level, -1, 0, &x, &y); break;
            case 'e': go_dir(width, height, level, 1, 0, &x, &y); break;
            case 'q': stop = true; break;
            default: printf("Commande invalide\n"); break;
        }

        print_terminal_map(width, height, level);

        if (check_victory(width, height, level)) {
            printf("\n>>> Victoire !\n");
            stop = true;
        }
    }

    free(level);
    return EXIT_SUCCESS;
}
