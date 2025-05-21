/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** run_game_scene
*/

#include "wolf3d.h"

void run_game_scene(data_t *data)
{
    handle_movement(data->assets.maps->walls, data);
    render_map(data);
}
