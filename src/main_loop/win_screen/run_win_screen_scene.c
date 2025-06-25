/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** run_win_screen_scene
*/

#include "wolf3d.h"

void run_win_screen_scene(data_t *data)
{
    if (sfKeyboard_isKeyPressed(sfKeyEnter)) {
        data->scene = MENU;
        if (data->arguments.debug)
            printf("switching to menu scene.\n");
        return;
    }
    render_win_screen(data);
}
