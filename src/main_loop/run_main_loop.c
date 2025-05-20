/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** run_main_loop
*/

#include "wolf3d.h"

void detect_mouse(data_t *data, menu_infos_t *menu_infos, char *game_state)
{
    if (sfFloatRect_contains(&menu_infos->newgame_infos,
    menu_infos->mouse_pos.x, menu_infos->mouse_pos.y))
        *game_state = GAME;
    if (sfFloatRect_contains(&menu_infos->continuegame_infos,
    menu_infos->mouse_pos.x, menu_infos->mouse_pos.y))
        printf("continuegame\n");
    if (sfFloatRect_contains(&menu_infos->options_infos,
    menu_infos->mouse_pos.x, menu_infos->mouse_pos.y))
        printf("options\n");
    if (sfFloatRect_contains(&menu_infos->lore_infos,
    menu_infos->mouse_pos.x, menu_infos->mouse_pos.y))
        printf("lore\n");
    if (sfFloatRect_contains(&menu_infos->exit_infos,
    menu_infos->mouse_pos.x, menu_infos->mouse_pos.y))
        printf("exit\n");
}

void verify_mouse(data_t *data, char *game_state)
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
    detect_mouse(data, &menu_infos, game_state);
}

void run_main_loop(data_t *data)
{
    sfEvent event;
    char game_state = MENU;
    sfVector2i mouse_pos = {0}; //temp

    set_sprite_positions(data);
    while (sfRenderWindow_isOpen(data->window)) {
        sfRenderWindow_display(data->window);
        sfRenderWindow_clear(data->window, sfBlack);
        manage_music(data, game_state);
        in_menu(data, game_state); //temp
        handle_movement(data->assets.maps->walls, data, game_state); //temp
        render_in_map(data, game_state); //temp
        while (sfRenderWindow_pollEvent(data->window, &event) == 0)
            continue;
        if (event.type == sfEvtClosed)
            break;
        if (event.mouseButton.button == sfMouseLeft)
            verify_mouse(data, &game_state);
    }
}
