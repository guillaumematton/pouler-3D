/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** terminate_game
*/

#include "wolf3d.h"

void terminate_game(data_t *data)
{
    if (data->arguments.debug)
        mini_printf("starting game termination.\n");
    sfRenderWindow_destroy(data->window);
    destroy_assets(data);
}
