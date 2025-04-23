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
    int nb_music = search_nb_music(data->assets.musics);
    sfMusic *music = pick_random_music(data->assets.musics, nb_music);

    while (sfRenderWindow_isOpen(data->window)) {
        sfRenderWindow_clear(data->window, sfBlack);
        if (sfMusic_getStatus(music) == sfStopped)
            music = pick_random_music(data->assets.musics, nb_music);
        in_menu(data);
        while (sfRenderWindow_pollEvent(data->window, &event) == 0)
            continue;
        if (event.type == sfEvtClosed)
            break;
    }
    return;
}
