/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** in_menu
*/

#include "wolf3d.h"

void render_menu(data_t *data)
{
    sfRenderWindow_drawSprite(data->window,
        data->sprites.menu.background, NULL);
    sfRenderWindow_drawSprite(data->window,
        data->sprites.menu.continue_game, NULL);
    sfRenderWindow_drawSprite(data->window, data->sprites.menu.new_game, NULL);
    sfRenderWindow_drawSprite(data->window, data->sprites.menu.options, NULL);
    sfRenderWindow_drawSprite(data->window, data->sprites.menu.lore, NULL);
    sfRenderWindow_drawSprite(data->window,
        data->sprites.menu.exit_game, NULL);
    sfRenderWindow_drawSprite(data->window, data->sprites.menu.title, NULL);
}
