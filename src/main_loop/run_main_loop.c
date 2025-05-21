/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** run_main_loop
*/

#include "wolf3d.h"

static void run_scenes(data_t *data)
{
    if (data->scene == MENU)
        run_menu_scene(data);
    if (data->scene == MENU)
        run_options_scene(data);
    if (data->scene == MENU)
        run_game_scene(data);
    if (data->scene == MENU)
        run_pause_scene(data);
}

void run_main_loop(data_t *data)
{
    sfVector2i mouse_pos = {0}; //temp

    set_sprite_positions(data);
    while (sfRenderWindow_isOpen(data->window) && data->exit == false) {
        sfRenderWindow_display(data->window);
        sfRenderWindow_clear(data->window, sfBlack);
        manage_music(data);
        while (sfRenderWindow_pollEvent(data->window, &data->event) == 0)
            continue;
        if (data->event.type == sfEvtClosed ||
            (sfKeyboard_isKeyPressed(sfKeyK) &&
                sfKeyboard_isKeyPressed(sfKeyLControl)))
            break;
        run_scenes(data);
    }
}
