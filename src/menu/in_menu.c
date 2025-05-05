/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** in_menu
*/

#include "wolf3d.h"

bool in_settings(data_t *data)
{
    return false;
}

bool in_menu(data_t *data)
{
    sfRenderWindow_drawSprite(data->window, data->sprites.menu.background, NULL);
    return false;
}
