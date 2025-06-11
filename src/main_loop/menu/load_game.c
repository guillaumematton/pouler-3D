/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** load_game
*/

#include "wolf3d.h"

static void load_player_data(data_t *data, char **lines)
{
    data->player.health = atof(lines[0]);
    data->player.x = atof(lines[1]);
    data->player.y = atof(lines[2]);
    data->player.dirX = atof(lines[3]);
    data->player.dirY = atof(lines[4]);
    data->player.planeX = atof(lines[5]);
    data->player.planeY = atof(lines[6]);
    set_new_map(data, lines[7]);
}

void load_game(data_t *data)
{
    char *buffer = my_readfile("save.dat");
    char **lines = my_strsplit(buffer, "\n", false);

    if (data->arguments.debug)
        my_putstr("loading a save.\n");
    if (buffer == NULL || lines == NULL ||
        my_ptrarraylen((void **) lines) < 8) {
        my_free(buffer);
        my_freestrarray(lines);
        if (data->arguments.debug)
            my_putstr("  failed to load the game save.\n");
        return;
    }
    load_player_data(data, lines);
    my_free(buffer);
    my_freestrarray(lines);
}
