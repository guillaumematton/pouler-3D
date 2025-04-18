/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** display_help
*/

#include "wolf3d.h"

bool display_help(data_t *data)
{
    if (data->arguments.help) {
        my_putstr("TODO HELP MSG.\n");
        return true;
    } else {
        return false;
    }
}
