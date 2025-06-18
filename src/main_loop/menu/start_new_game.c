/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** start_new_game
*/

#include "wolf3d.h"

void start_new_game(data_t *data)
{
    data->score = 0;
    data->game_time = 0;
    set_new_map(data, "start.lvl");
}
