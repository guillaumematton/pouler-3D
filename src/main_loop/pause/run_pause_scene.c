/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** run_pause_scene
*/

#include "wolf3d.h"

void run_pause_scene(data_t *data)
{
    if (sfKeyboard_isKeyPressed(sfKeyF1)) {
        data->scene = GAME;
        return;
    }
}
