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
    if (data->arguments.debug)
        mini_printf("playing %s\n", music->name);
    sfMusic_setLoop(data->current_music, sfFalse);
    data->current_music_name = music->name;
    return music->music;
}

static void run_menu_music(data_t *data)
{
    music_t *music = data->assets.musics;

    if (data->current_music == NULL ||
        data->current_music_name == NULL ||
        sfMusic_getStatus(data->current_music) == sfStopped ||
        my_strcmp(data->current_music_name, "menu.ogg") != 0) {
        for (; music != NULL && my_strcmp("menu.ogg", music->name) != 0;
            music = music->next);
        if (music == NULL)
            return;
        data->current_music = music->music;
        data->current_music_name = music->name;
        sfMusic_setLoop(data->current_music, sfTrue);
        sfMusic_play(data->current_music);
    }
}

void manage_music(data_t *data)
{
    if (data->current_music)
        sfMusic_setVolume(data->current_music, data->volume);
    if (data->scene == MENU || data->scene == MENU_OPTIONS) {
        run_menu_music(data);
        return;
    }
    if (data->current_music_name &&
        my_strcmp(data->current_music_name, "menu.ogg") == 0)
        sfMusic_stop(data->current_music);
    if (data->scene == LORE)
        return;
    if (data->current_music == NULL ||
        data->current_music_name == NULL ||
        sfMusic_getStatus(data->current_music) == sfStopped ||
        my_strcmp(data->current_music_name, "menu.ogg") == 0) {
        data->current_music = pick_random_music(data);
        sfMusic_play(data->current_music);
    }
}
