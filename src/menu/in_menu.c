/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** in_menu
*/

#include "wolf3d.h"

void in_settings(data_t *data)
{
    return;
}

void run_menu_music(data_t *data)
{
    music_t *music = data->assets.musics;

    if (data->current_music == NULL ||
        data->current_music_name == NULL ||
        sfMusic_getStatus(data->current_music) == sfStopped ||
        my_strcmp(data->current_music_name, "music.ogg") != 0) {
        for (; music != NULL && my_strcmp("menu.ogg", music->name) != 0;
            music = music->next);
        if (music == NULL)
            return;
        data->current_music = music->music;
        data->current_music_name = music->name;
        sfMusic_play(data->current_music);
    }
}

void in_menu(data_t *data, char game_state)
{
    if (game_state == OPTIONS || game_state == MENU)
        run_menu_music(data);
    if (game_state == OPTIONS)
        in_settings(data);
    if (game_state != MENU)
        return;
    sfRenderWindow_drawSprite(data->window,
        data->sprites.menu.background, NULL);
    sfRenderWindow_drawSprite(data->window,
        data->sprites.menu.continue_game, NULL);
    sfRenderWindow_drawSprite(data->window, data->sprites.menu.new_game, NULL);
    sfRenderWindow_drawSprite(data->window, data->sprites.menu.options, NULL);
    sfRenderWindow_drawSprite(data->window, data->sprites.menu.lore, NULL);
    sfRenderWindow_drawSprite(data->window,
        data->sprites.menu.exit_game, NULL);
    sfRenderWindow_drawSprite(data->window, data->sprites.menu.title, NULL);
}
