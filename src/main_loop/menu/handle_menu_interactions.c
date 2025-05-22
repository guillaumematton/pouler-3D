/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** handle_menu_interactions
*/

#include "wolf3d.h"

static void detect_button_mouse_click(data_t *data, menu_infos_t *menu_infos)
{
    if (sfFloatRect_contains(&menu_infos->newgame_infos,
    menu_infos->mouse_pos.x, menu_infos->mouse_pos.y))
        data->scene = GAME;
    if (sfFloatRect_contains(&menu_infos->continuegame_infos,
    menu_infos->mouse_pos.x, menu_infos->mouse_pos.y))
        printf("continuegame\n");
    if (sfFloatRect_contains(&menu_infos->options_infos,
    menu_infos->mouse_pos.x, menu_infos->mouse_pos.y))
        data->scene = OPTIONS;
    if (sfFloatRect_contains(&menu_infos->lore_infos,
    menu_infos->mouse_pos.x, menu_infos->mouse_pos.y))
        printf("lore\n");
    if (sfFloatRect_contains(&menu_infos->exit_infos,
    menu_infos->mouse_pos.x, menu_infos->mouse_pos.y))
        data->exit = true;
}

static void handle_button_clicks(data_t *data)
{
    menu_infos_t menu_infos = {{0}, {0}, {0}, {0}, {0}, {0}};

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
    detect_button_mouse_click(data, &menu_infos);
}

void handle_menu_interactions(data_t *data)
{
    if (data->event.mouseButton.button == sfMouseLeft)
        handle_button_clicks(data);
}
