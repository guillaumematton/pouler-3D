/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** run_options_scene
*/

#include "wolf3d.h"

static void set_options_sprites_fullscreen(data_t *data)
{
    sfVector2f scale = {4, 6};
    sfVector2f position = {0, 0};

    sfSprite_setPosition(data->sprites.menu.o_background, position);
        sfSprite_setScale(data->sprites.menu.o_background, scale);
        set_position_scale(1.6, 550, 200,
    data->sprites.menu.options_sprites.full_screen);
        set_position_scale(0.6, 800, 750,
    data->sprites.menu.options_sprites.volume);
        set_position_scale(0.6, 1050, 775,
    data->sprites.menu.options_sprites.volume_up);
        set_position_scale(0.6, 550, 775,
    data->sprites.menu.options_sprites.volume_down);
}

static void set_options_sprites_window(data_t *data)
{
    sfVector2f scale = {1.9, 3};
    sfVector2f position = {0, 0};

    sfSprite_setPosition(data->sprites.menu.o_background, position);
        sfSprite_setScale(data->sprites.menu.o_background, scale);
        set_position_scale(0.8, 210, 100,
    data->sprites.menu.options_sprites.full_screen);
        set_position_scale(0.3, 340, 410,
    data->sprites.menu.options_sprites.volume);
        set_position_scale(0.3, 475, 410,
    data->sprites.menu.options_sprites.volume_up);
        set_position_scale(0.3, 200, 410,
    data->sprites.menu.options_sprites.volume_down);
}

static void set_sprite_positions_options(data_t *data)
{
    if (!data->arguments.full_screen)
        set_options_sprites_window(data);
    else
        set_options_sprites_fullscreen(data);
    return;
}

void run_menu_options_scene(data_t *data)
{
    set_sprite_positions_options(data);
    render_options(data);
    handle_options_interactions(data);
    if (sfKeyboard_isKeyPressed(sfKeyEnter)) {
        data->scene = MENU;
        if (data->arguments.debug)
            my_putstr("switching to menu scene.\n");
        return;
    }
}

void run_game_options_scene(data_t *data)
{
    set_sprite_positions_options(data);
    handle_options_interactions(data);
    render_options(data);
    if (sfKeyboard_isKeyPressed(sfKeyEnter)) {
        data->scene = PAUSE;
        if (data->arguments.debug)
            my_putstr("switching to pause scene.\n");
        return;
    }
}
