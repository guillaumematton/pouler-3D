/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** main_loop
*/

#include "wolf3d.h"

void run_loop(data_t *data)
{
    sfEvent event;
    char game_state = MENU;
    sfVector2i mouse_pos = {0};
    sfVector2f newgame_pos = {0};

    newgame_pos = sfSprite_getPosition(data->sprites.menu.new_game);
    while (sfRenderWindow_isOpen(data->window)) {
        sfRenderWindow_display(data->window);
        sfRenderWindow_clear(data->window, sfBlack);
        manage_music(data, game_state);
        in_menu(data, game_state);
        handle_movement(data->assets.maps->walls, data, game_state);
        render_in_map(data, game_state);
        while (sfRenderWindow_pollEvent(data->window, &event) == 0)
            continue;
        if (event.type == sfEvtClosed)
            break;
        if (event.mouseButton.button == sfMouseLeft) {
            mouse_pos = sfMouse_getPositionRenderWindow(data->window);
            if (mouse_pos.x >= newgame_pos.x && mouse_pos.x <=
                newgame_pos.x + 266 && mouse_pos.y >= newgame_pos.y + 85 &&
                mouse_pos.y <= newgame_pos.y + 116) {
                game_state = GAME;
            }
        }
    }
}
