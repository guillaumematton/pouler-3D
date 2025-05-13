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

    data->sprites.in_full_screen = false;
    if (data->arguments.full_screen) {
        arg = sfClose | sfFullscreen;
        mode.width = 1920;
        mode.height = 1080;
        data->sprites.in_full_screen = true;
    }
    window = sfRenderWindow_create(mode, "wolf3D",
        arg, NULL);
    if (!window)
        return true;
    sfRenderWindow_setVerticalSyncEnabled(window, sfTrue);
    data->window = window;
    return false;
}

void initialize_player(data_t *data)
{
    data->player.health = 100;
    data->player.x = 0;
    data->player.y = 0;
    data->player.dirX = -1;
    data->player.dirY = 0;
    data->player.planeX = 0;
    data->player.planeY = 0.90; // 90 ° FOV
}

//does all the neccessary work to start the game (which you just lost)
//returns true if error
bool initialize_game(data_t *data)
{
    if (data->arguments.debug)
        mini_printf("starting game initialization.\n");
    if (set_window(data))
        return true;
    if (load_assets(data))
        return true;
    if (create_menu_sprites(data))
        return true;
    return false;
}
