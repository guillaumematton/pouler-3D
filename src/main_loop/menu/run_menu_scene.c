/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** run_menu_scene
*/

#include "wolf3d.h"

void run_menu_scene(data_t *data)
{
    set_sprite_positions(data);
    render_menu(data);
    handle_menu_interactions(data);
}
