/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** run_pause_scene
*/

#include "wolf3d.h"

static void set_fullscreen_pause(data_t *data)
{
    sfVector2f scale = {5, 6};
    sfVector2f position = {0, 0};

    sfSprite_setPosition(data->sprites.menu.p_background, position);
    sfSprite_setScale(data->sprites.menu.p_background, scale);
    set_position_scale(1, 730, 100, data->sprites.menu.options);
    set_position_scale(1, 760, 900, data->sprites.menu.exit_game);
    set_position_scale(1, 1400, 400,
    data->sprites.menu.options_sprites.save);
}

static void set_sprite_positions_pause(data_t *data)
{
    sfVector2f scale = {1.9, 3};
    sfVector2f position = {0, 0};

    if (!data->arguments.full_screen) {
        sfSprite_setPosition(data->sprites.menu.p_background, position);
        sfSprite_setScale(data->sprites.menu.p_background, scale);
        set_position_scale(0.35, 330, 150, data->sprites.menu.options);
        set_position_scale(0.3, 347, 500, data->sprites.menu.exit_game);
        set_position_scale(0.3, 600, 300,
    data->sprites.menu.options_sprites.save);
    } else
        set_fullscreen_pause(data);
    return;
}

void run_pause_scene(data_t *data)
{
    set_sprite_positions_pause(data);
    render_pause(data);
    handle_pause_interactions(data);
    if (sfKeyboard_isKeyPressed(sfKeyEnter)) {
        data->scene = GAME;
        if (data->arguments.debug)
            mini_printf("swithcing to game scene.\n");
        return;
    }
}
