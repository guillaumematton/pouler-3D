/*
** EPITECH PROJECT, 2025
** jukebox
** File description:
** create a list of music playing randomly
*/

#include "wolf3d.h"

int random_int(int min, int max)
{
    int random;

    random = min + rand() % (max - min + 1);
    return random;
}

sfMusic *add_music_no_loop(sfMusic *music)
{
    sfMusic_play(music);
    return music;
}

int search_nb_music(music_t *pl)
{
    music_t *temp = pl;
    int nb_music = 0;

    if (!temp)
        return -1;
    while (temp != NULL) {
        nb_music += 1;
        temp = temp->next;
    }
    return nb_music;
}

sfMusic *pick_random_music(music_t *pl, int nb_music)
{
    int music_id = random_int(0, nb_music - 1);
    music_t *temp = pl;

    for (int i = 0; i < music_id; i += 1)
        temp = temp->next;
    return add_music_no_loop(temp->music);
}

void manage_music(sfMusic **music, data_t *data, int nb_music)
{
    if (sfMusic_getStatus(*music) == sfStopped)
        *music = pick_random_music(data->assets.musics, nb_music);
    return;
}
