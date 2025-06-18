/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** handle_menu_interactions
*/

#include "wolf3d.h"

static void detect_button_mouse_click_new_game_continue(data_t *data,
    menu_infos_t *menu_infos)
{
    if (sfFloatRect_contains(&menu_infos->newgame_infos,
        menu_infos->mouse_pos.x, menu_infos->mouse_pos.y)) {
        data->scene = GAME;
        start_new_game(data);
        if (data->arguments.debug)
            my_putstr("switching to game scene.\n");
    }
    if (sfFloatRect_contains(&menu_infos->continuegame_infos,
        menu_infos->mouse_pos.x, menu_infos->mouse_pos.y)) {
        load_game(data);
        data->scene = GAME;
        if (data->arguments.debug)
            my_putstr("switching to game scene.\n");
    }
}

static void detect_button_mouse_click_options_lore_exit(data_t *data,
    menu_infos_t *menu_infos)
{
    if (sfFloatRect_contains(&menu_infos->options_infos,
        menu_infos->mouse_pos.x, menu_infos->mouse_pos.y)) {
        data->scene = MENU_OPTIONS;
        if (data->arguments.debug)
            my_putstr("switching to menu options scene.\n");
    }
    if (sfFloatRect_contains(&menu_infos->lore_infos,
    menu_infos->mouse_pos.x, menu_infos->mouse_pos.y)) {
        browse_sounds(data);
        data->scene = LORE;
        if (data->arguments.debug)
            my_putstr("switching to lore scene.\n");
    }
    if (sfFloatRect_contains(&menu_infos->exit_infos,
        menu_infos->mouse_pos.x, menu_infos->mouse_pos.y)) {
        data->exit = true;
        if (data->arguments.debug)
            my_putstr("exiting game.\n");
    }
}

static void handle_button_clicks(data_t *data)
{
    menu_infos_t menu_infos = {{0, 0, 0, 0}, {0, 0, 0, 0},
        {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0}};

    menu_infos.mouse_pos =
    sfMouse_getPositionRenderWindow(data->window);
    menu_infos.newgame_infos =
    sfSprite_getGlobalBounds(data->sprites.menu.new_game);
    menu_infos.continuegame_infos = sfSprite_getGlobalBounds(
    data->sprites.menu.continue_game);
    menu_infos.options_infos =
    sfSprite_getGlobalBounds(data->sprites.menu.options);
    menu_infos.lore_infos = sfSprite_getGlobalBounds(data->sprites.menu.lore);
    menu_infos.exit_infos =
    sfSprite_getGlobalBounds(data->sprites.menu.exit_game);
    detect_button_mouse_click_new_game_continue(data, &menu_infos);
    detect_button_mouse_click_options_lore_exit(data, &menu_infos);
}

void handle_menu_interactions(data_t *data)
{
    if (data->event.mouseButton.button == sfMouseLeft)
        handle_button_clicks(data);
}
