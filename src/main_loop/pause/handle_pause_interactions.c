/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** handle_menu_interactions
*/

#include "wolf3d.h"

static void detect_button_mouse_click(data_t *data, pause_infos_t *pause_infos)
{
    if (sfFloatRect_contains(&pause_infos->options_infos,
        pause_infos->mouse_pos.x, pause_infos->mouse_pos.y)) {
        data->scene = GAME_OPTIONS;
        if (data->arguments.debug)
            my_putstr("switching to game options scene.\n");
    }
    if (sfFloatRect_contains(&pause_infos->exit_infos,
        pause_infos->mouse_pos.x, pause_infos->mouse_pos.y)) {
        data->exit = true;
        if (data->arguments.debug)
            my_putstr("exiting game.\n");
    }
    if (sfFloatRect_contains(&pause_infos->save_infos,
    pause_infos->mouse_pos.x, pause_infos->mouse_pos.y))
        save_game(data);
}

static void handle_button_clicks(data_t *data)
{
    pause_infos_t pause_infos = {{0, 0, 0, 0}, {0, 0, 0, 0},
    {0, 0, 0, 0}, {0, 0}};

    pause_infos.mouse_pos =
    sfMouse_getPositionRenderWindow(data->window);
    pause_infos.options_infos =
    sfSprite_getGlobalBounds(data->sprites.menu.options);
    pause_infos.exit_infos =
    sfSprite_getGlobalBounds(data->sprites.menu.exit_game);
    pause_infos.save_infos =
    sfSprite_getGlobalBounds(data->sprites.menu.options_sprites.save);
    detect_button_mouse_click(data, &pause_infos);
}

void handle_pause_interactions(data_t *data)
{
    if (data->event.mouseButton.button == sfMouseLeft)
            handle_button_clicks(data);
}
