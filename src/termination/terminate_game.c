/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** terminate_game
*/

#include "wolf3d.h"

static void destroy_menu_sprites(data_t *data)
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

static void destroy_gui_sprites(data_t *data)
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
    if (data->sprites.menu.p_background)
        sfSprite_destroy(data->sprites.menu.p_background);
}

static void destroy_wall_images(data_t *data)
{
    if (data->sprites.environment.A)
        sfImage_destroy(data->sprites.environment.A);
    if (data->sprites.environment.B)
        sfImage_destroy(data->sprites.environment.B);
    if (data->sprites.environment.C)
        sfImage_destroy(data->sprites.environment.C);
    if (data->sprites.environment.D)
        sfImage_destroy(data->sprites.environment.D);
    if (data->sprites.environment.E)
        sfImage_destroy(data->sprites.environment.E);
    if (data->sprites.environment.F)
        sfImage_destroy(data->sprites.environment.F);
    if (data->sprites.environment.G)
        sfImage_destroy(data->sprites.environment.G);
    if (data->sprites.environment.H)
        sfImage_destroy(data->sprites.environment.H);
    if (data->sprites.environment.I)
        sfImage_destroy(data->sprites.environment.I);
}

static void destroy_miscellanous(data_t *data)
{
    if (data->clock)
        sfClock_destroy(data->clock);
    if (data->game_vertex)
        sfVertexArray_destroy(data->game_vertex);
}

void terminate_game(data_t *data)
{
    if (data->arguments.debug)
        mini_printf("starting game termination.\n");
    sfRenderWindow_destroy(data->window);
    destroy_assets(data);
    destroy_wall_images(data);
    destroy_gui_sprites(data);
    destroy_miscellanous(data);
}
