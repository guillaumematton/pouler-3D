/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** bind_assets
*/

#include "wolf3d.h"

bool bind_assets(data_t *data)
{
    if (data->arguments.debug)
        my_putstr("  binding assets.\n");
    if (bind_weapon_assets(data))
        return true;
    return false;
}
