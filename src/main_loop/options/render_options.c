/*
** EPITECH PROJECT, 2025
** render_pause
** File description:
** render the pause menu
*/

#include "wolf3d.h"

void render_options(data_t *data)
{
    sfRenderWindow_drawSprite(data->window,
        data->sprites.menu.o_background, NULL);
    sfRenderWindow_drawSprite(data->window,
        data->sprites.menu.options_sprites.full_screen, NULL);
    sfRenderWindow_drawSprite(data->window,
        data->sprites.menu.options_sprites.volume, NULL);
    sfRenderWindow_drawSprite(data->window,
        data->sprites.menu.options_sprites.volume_up, NULL);
    sfRenderWindow_drawSprite(data->window,
        data->sprites.menu.options_sprites.volume_down, NULL);
}
