/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** render_stats_text
*/

#include "wolf3d.h"

static void render_stats_text(data_t *data)
{
    char buffer[21] = "\0";

    sprintf(buffer, "score: %i\ntime: %.2fs",
        data->score,
        data->game_time);
    sfText_setString(data->hud_text, buffer);
    sfRenderWindow_drawText(data->window, data->hud_text, NULL);
}

void render_win_screen(data_t *data)
{
    if (!data->arguments.full_screen) {
        set_position_scale(1.2, 0, 0, data->sprites.win_screen.background);
    } else {
        set_position_scale(3, 0, 0, data->sprites.win_screen.background);
    }
    sfRenderWindow_drawSprite(data->window,
        data->sprites.win_screen.background, NULL);
    render_stats_text(data);
}
