/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** run_game_scene
*/

#include "wolf3d.h"

void run_game_scene(data_t *data)
{
    if (sfKeyboard_isKeyPressed(sfKeyEscape)) {
        data->scene = PAUSE;
        return;
    }
    handle_firearms(data);
    handle_movement(data->assets.maps->walls, data);
    render_map(data);
    sfRenderWindow_drawSprite(data->window,
    data->current_weapon.current_sprite, NULL);
}
