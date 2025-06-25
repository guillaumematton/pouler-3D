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
    if (data->sprites.menu.options_sprites.back)
        sfSprite_destroy(data->sprites.menu.options_sprites.back);
    if (data->sprites.menu.p_background)
        sfSprite_destroy(data->sprites.menu.p_background);
    if (data->sprites.menu.p_background)
        sfSprite_destroy(data->sprites.menu.o_background);
    if (data->sprites.menu.p_background)
        sfSprite_destroy(data->sprites.menu.options_sprites.volume);
    if (data->sprites.menu.p_background)
        sfSprite_destroy(data->sprites.menu.options_sprites.volume_up);
    if (data->sprites.menu.p_background)
        sfSprite_destroy(data->sprites.menu.options_sprites.volume_down);
    if (data->sprites.menu.p_background)
        sfSprite_destroy(data->sprites.menu.options_sprites.save);
}

static void destroy_wall_images(data_t *data)
{
    env_t *list = data->sprites.environment;
    env_t *next_list = NULL;

    for (; list != NULL; list = next_list) {
        next_list = list->next;
        sfImage_destroy(list->image);
        free(list);
    }
}

static void destroy_miscellanous(data_t *data)
{
    if (data->clock)
        sfClock_destroy(data->clock);
    if (data->game_screen)
        sfSprite_destroy(data->game_screen);
    if (data->game_screen_text)
        sfTexture_destroy(data->game_screen_text);
    if (data->game_screen_image)
        sfImage_destroy(data->game_screen_image);
    if (data->tile)
        sfRectangleShape_destroy(data->tile);
    if (data->sprites.win_screen.background)
        sfSprite_destroy(data->sprites.win_screen.background);
}

static void destroy_text(data_t *data)
{
    if (data->hud_text != NULL)
        sfText_destroy(data->hud_text);
}

static void destroy_lore(data_t *data)
{
    if (data->sprites.menu.lore_sprites.lore1)
        sfSprite_destroy(data->sprites.menu.lore_sprites.lore1);
    if (data->sprites.menu.lore_sprites.lore2)
        sfSprite_destroy(data->sprites.menu.lore_sprites.lore2);
    if (data->sprites.menu.lore_sprites.lore3)
        sfSprite_destroy(data->sprites.menu.lore_sprites.lore3);
    if (data->sprites.menu.lore_sprites.lore4)
        sfSprite_destroy(data->sprites.menu.lore_sprites.lore4);
    if (data->sprites.menu.lore_sprites.lore5)
        sfSprite_destroy(data->sprites.menu.lore_sprites.lore5);
    if (data->sprites.menu.lore_sprites.lore6)
        sfSprite_destroy(data->sprites.menu.lore_sprites.lore6);
    if (data->sprites.menu.lore_sprites.lore7)
        sfSprite_destroy(data->sprites.menu.lore_sprites.lore7);
    if (data->sprites.menu.lore_sprites.lore8)
        sfSprite_destroy(data->sprites.menu.lore_sprites.lore8);
    if (data->sprites.menu.lore_sprites.lore9)
        sfSprite_destroy(data->sprites.menu.lore_sprites.lore9);
}

void terminate_game(data_t *data)
{
    if (data->arguments.debug)
        mini_printf("starting game termination.\n");
    if (data->arguments.debug)
        mini_printf("  destroying window.\n");
    sfRenderWindow_close(data->window);
    sfRenderWindow_destroy(data->window);
    destroy_assets(data);
    destroy_wall_images(data);
    destroy_gui_sprites(data);
    destroy_miscellanous(data);
    destroy_text(data);
    destroy_lore(data);
}
