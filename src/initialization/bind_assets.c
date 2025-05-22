/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** bind_assets
*/

#include "wolf3d.h"

void bind_assets(data_t *data)
{
    if (data->arguments.debug)
        my_putstr("  binding assets.\n");
    bind_weapon_assets(data);
}
