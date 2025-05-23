/*
** EPITECH PROJECT, 2025
** render_pause
** File description:
** render the pause menu
*/

#include "wolf3d.h"

void render_pause(data_t *data)
{
    sfRenderWindow_drawSprite(data->window,
        data->sprites.menu.p_background, NULL);
    sfRenderWindow_drawSprite(data->window, data->sprites.menu.options, NULL);
    sfRenderWindow_drawSprite(data->window,
        data->sprites.menu.exit_game, NULL);
    sfRenderWindow_drawSprite(data->window,
        data->sprites.menu.options_sprites.save, NULL);
}
