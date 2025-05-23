/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** run_main_loop
*/

#include "wolf3d.h"

static void run_scenes(data_t *data)
{
    static int last_scene = MENU;

    if (data->scene == GAME && last_scene != GAME)
        sfRenderWindow_setMouseCursorVisible(data->window, sfFalse);
    if (data->scene != GAME && last_scene == GAME)
        sfRenderWindow_setMouseCursorVisible(data->window, sfTrue);
    last_scene = data->scene;
    if (data->scene == MENU)
        run_menu_scene(data);
    if (data->scene == MOPTIONS)
        run_moptions_scene(data);
    if (data->scene == GOPTIONS)
        run_goptions_scene(data);
    if (data->scene == GAME)
        run_game_scene(data);
    if (data->scene == PAUSE)
        run_pause_scene(data);
}

void run_main_loop(data_t *data)
{
    while (sfRenderWindow_isOpen(data->window) && data->exit == false) {
        sfRenderWindow_display(data->window);
        sfRenderWindow_clear(data->window, sfBlack);
        manage_music(data);
        manage_time(data);
        while (sfRenderWindow_pollEvent(data->window, &data->event) == 0)
            continue;
        if (data->event.type == sfEvtClosed ||
            (sfKeyboard_isKeyPressed(sfKeyK) &&
                sfKeyboard_isKeyPressed(sfKeyLControl)))
            break;
        run_scenes(data);
    }
}
