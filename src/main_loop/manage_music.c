/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** manage_music
*/

#include "wolf3d.h"

static int random_int(int min, int max)
{
    int random;

    random = min + rand() % (max - min + 1);
    return random;
}

static int get_music_count(data_t *data)
{
    music_t *music = data->assets.musics;
    int music_count = 0;

    if (music == NULL)
        return -1;
    while (music != NULL) {
        music_count += 1;
        music = music->next;
    }
    return music_count;
}

static sfMusic *pick_random_music(data_t *data)
{
    int music_count = get_music_count(data);
    int music_id = random_int(0, music_count - 1);
    music_t *music = data->assets.musics;

    for (int i = 0; i < music_id; i += 1)
        music = music->next;
    mini_printf("playing %s\n", music->name);
    return music->music;
}

void manage_music(data_t *data)
{
    if (sfMusic_getStatus(data->current_music) == sfStopped ||
        data->current_music == NULL) {
        data->current_music = pick_random_music(data);
        sfMusic_play(data->current_music);
        }
}
