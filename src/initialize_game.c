/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** initialize_game
*/

#include "wolf3d.h"

//returns true if error
bool set_window(data_t *data)
{
    sfVideoMode mode = {800, 600, 32};
    sfRenderWindow *window = NULL;
    int arg = sfClose;

    if (data->arguments.full_screen) {
        arg = sfClose | sfFullscreen;
        mode.width = 1920;
        mode.height = 1080;
    }
    window = sfRenderWindow_create(mode, "wolf3D",
        arg, NULL);
    if (!window)
        return true;
    sfRenderWindow_setVerticalSyncEnabled(window, sfTrue);
    data->window = window;
    return false;
}

//does all the neccessary work to start the game (which you just lost)         
//returns true if error
bool initialize_game(data_t *data)
{
    if (load_data(data))
        return true;
    if (set_window(data))
        return true;
    return false;
}
