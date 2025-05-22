/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** run_options_scene
*/

#include "wolf3d.h"

static void set_sprite_positions_moptions(data_t *data)
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
    return;
}

void run_moptions_scene(data_t *data)
{
    set_sprite_positions_moptions(data);
    render_moptions(data);
    handle_moptions_interactions(data);
    if (sfKeyboard_isKeyPressed(sfKeyEnter)) {
        data->scene = MENU;
        return;
    }
}
