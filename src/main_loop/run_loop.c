/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** main_loop
*/

#include "wolf3d.h"

void run_loop(data_t *data)
{
    sfEvent event;

    while (sfRenderWindow_isOpen(data->window)) {
        sfRenderWindow_clear(data->window, sfBlack);
        while (sfRenderWindow_pollEvent(data->window, &event) == 0)
            continue;
	if (event.type == sfEvtClosed)
            break;
    }
    return;
}
