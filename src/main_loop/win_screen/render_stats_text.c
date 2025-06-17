/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** render_stats_text
*/

#include "wolf3d.h"

void render_stats_text(data_t *data)
{
    char buffer[21] = "\0";

    sprintf(buffer, "score: %i\ntime: %.2fs",
        data->score,
        data->game_time);
    sfText_setString(data->hud_text, buffer);
    sfRenderWindow_drawText(data->window, data->hud_text, NULL);
}
