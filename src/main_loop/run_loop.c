/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** main_loop
*/

#include "wolf3d.h"

void set_position_scale(float scale_value, float positionx,
    float positiony, sfSprite *sprite)
{
    sfVector2f scale = {scale_value, scale_value};
    sfVector2f position = {positionx, positiony};

    sfSprite_setPosition(sprite, position);
    sfSprite_setScale(sprite, scale);
    return;
}

void set_all(data_t *data)
{
    set_position_scale(1.38, 0, 0, data->sprites.menu.background);
    set_position_scale(0.5, 250, 175, data->sprites.menu.new_game);
    set_position_scale(0.375, 290, 260, data->sprites.menu.continue_game);
    set_position_scale(0.45, 290, 290, data->sprites.menu.options);
    set_position_scale(0.425, 300, 355, data->sprites.menu.lore);
    set_position_scale(0.3, 315, 460, data->sprites.menu.exit_game);
    set_position_scale(0.8, 0, 0, data->sprites.menu.title);
    return;
}

void run_loop(data_t *data)
{
    sfEvent event;
    char game_state = MENU;
    sfVector2i mouse_pos = {0};
    sfVector2f newgame_pos = {0};

    set_all(data);
    newgame_pos = sfSprite_getPosition(data->sprites.menu.new_game);
    while (sfRenderWindow_isOpen(data->window)) {
        sfRenderWindow_display(data->window);
        sfRenderWindow_clear(data->window, sfBlack);
        manage_music(data, game_state);
        in_menu(data, game_state);
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
