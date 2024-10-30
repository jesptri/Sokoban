#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>

#include "sokoban.h"
#include "loader.h"
#include "gui.h"

typedef struct my_map my_map;

int main(int argc, char * argv[])

{

    my_map * map_to_play = loader(argv[1]);

    int width = map_to_play->width;
    int height = map_to_play->height;

    char * map = map_to_play->map;

    GUI_init("Window for Sokoban game", width, height);

    GUI_show_map_to_play(width, height, map);

    // I prefer use an int instead of true and false, but there is no difference

    int A = 0 ;

    while(A == 0)

    {

        switch(GUI_get_key())

        {

        case SDLK_UP:
            map_to_play = move('N', map_to_play);
            GUI_show_map_to_play(width, height, map);
            break;
        case SDLK_DOWN:
            map_to_play = move('S', map_to_play);
            GUI_show_map_to_play(width, height, map);
            break;
        case SDLK_RIGHT:
            map_to_play = move('E', map_to_play);
            GUI_show_map_to_play(width, height, map);
            break;
        case SDLK_LEFT:
            map_to_play = move('O', map_to_play);
            GUI_show_map_to_play(width, height, map);
            break;
        case 'q':
            A = 1;
            break;

        }

        if (A != 0)

        {
            break;
        }

    }

    GUI_close();

    return EXIT_SUCCESS;

}
