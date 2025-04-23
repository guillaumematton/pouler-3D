/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** in_menu
*/

#include "wolf3d.h"

int in_settings(data_t *data)
{
    return 0;
}

bool create_menu_sprites(data_t *data)
{
    if (create_menu_background(data))
        return true;
    return false;
}

bool in_menu(data_t *data)
{
    data->sprites.menu = malloc(sizeof(data_t));
    if (!data->sprites.menu)
        return true;
    if (create_menu_sprites(data))
        return true;
    return false;
}
