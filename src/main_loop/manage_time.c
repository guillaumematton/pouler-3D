/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** manage_time
** printf("%.2f\n", 1.0 / sfTime_asSeconds(elapsed));
*/

#include "wolf3d.h"

void manage_time(data_t *data)
{
    sfTime elapsed = sfClock_getElapsedTime(data->clock);

    while (sfTime_asSeconds(elapsed) < 1.0 / GAME_FPS) {
        elapsed = sfClock_getElapsedTime(data->clock);
    }
    sfClock_restart(data->clock);
    data->tick_duration = sfTime_asSeconds(elapsed);
    if (data->scene == GAME || data->scene == LORE)
        data->game_time += data->tick_duration;
}
