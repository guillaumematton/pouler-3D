/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** terminate_game
*/

#include "wolf3d.h"

void destroy_menu_sprites(data_t *data)
{
    if (data->sprites.menu.title)
        sfSprite_destroy(data->sprites.menu.title);
    if (data->sprites.menu.background)
        sfSprite_destroy(data->sprites.menu.background);
    if (data->sprites.menu.new_game)
        sfSprite_destroy(data->sprites.menu.new_game);
    if (data->sprites.menu.continue_game)
        sfSprite_destroy(data->sprites.menu.continue_game);
    if (data->sprites.menu.options)
        sfSprite_destroy(data->sprites.menu.options);
    if (data->sprites.menu.lore)
        sfSprite_destroy(data->sprites.menu.lore);
    if (data->sprites.menu.exit_game)
        sfSprite_destroy(data->sprites.menu.exit_game);
}

void destroy_gui_sprites(data_t *data)
{
    destroy_menu_sprites(data);
    if (data->sprites.menu.options_sprites.full_screen)
        sfSprite_destroy(data->sprites.menu.options_sprites.full_screen);
    if (data->sprites.menu.options_sprites.empty_box)
        sfSprite_destroy(data->sprites.menu.options_sprites.empty_box);
    if (data->sprites.menu.options_sprites.full_box)
        sfSprite_destroy(data->sprites.menu.options_sprites.full_box);
    if (data->sprites.menu.options_sprites.back)
        sfSprite_destroy(data->sprites.menu.options_sprites.back);
}

void terminate_game(data_t *data)
{
    if (data->arguments.debug)
        mini_printf("starting game termination.\n");
    sfRenderWindow_destroy(data->window);
    destroy_assets(data);
}
