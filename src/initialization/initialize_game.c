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
    int arg = sfClose;

    data->clock = sfClock_create();
    if (!data->clock)
        return true;
    if (data->arguments.full_screen) {
        arg = sfClose | sfFullscreen;
        mode.width = 1920;
        mode.height = 1080;
    }
    data->window = sfRenderWindow_create(mode, "wolf3D",
        arg, NULL);
    if (!data->window)
        return true;
    sfRenderWindow_setFramerateLimit(data->window, 60);
    data->screen_size = sfRenderWindow_getSize(data->window);
    return false;
}

void initialize_player(data_t *data)
{
    data->player.health = 100;
    data->player.x = 2;
    data->player.y = 2;
    data->player.dirX = 1;
    data->player.dirY = 0;
    data->player.planeX = 0;
    data->player.planeY = 0.9;
}

//does all the neccessary work to start the game (which you just lost)
//returns true if error
bool initialize_game(data_t *data)
{
    data->game_vertex = sfVertexArray_create();
    if (!data->game_vertex)
        return true;
    sfVertexArray_setPrimitiveType(data->game_vertex, sfPoints);
    if (data->arguments.debug)
        mini_printf("starting game initialization.\n");
    if (set_window(data))
        return true;
    initialize_player(data);
    if (load_assets(data))
        return true;
    if (create_menu_sprites(data) || create_wall_images(data))
        return true;
    return false;
}
