/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** handle_menu_interactions
*/

#include "wolf3d.h"

static void toggle_fullscreen(data_t *data)
{
    sfVideoMode mode = {0};
    int arg = 0;

    mode.width = 1920;
    mode.height = 1080;
    mode.bitsPerPixel = 32;
    arg = sfClose | sfFullscreen;
    sfRenderWindow_destroy(data->window);
    data->window = sfRenderWindow_create(mode, "wolf3D", arg, NULL);
    data->arguments.full_screen = true;
}

static void disable_fullscreen(data_t *data)
{
    sfVideoMode mode = {0};
    int arg = 0;

    mode.width = 800;
    mode.height = 600;
    mode.bitsPerPixel = 32;
    arg = sfClose;
    sfRenderWindow_destroy(data->window);
    data->window = sfRenderWindow_create(mode, "wolf3D", arg, NULL);
    data->arguments.full_screen = false;
}

static void detect_volume_click(data_t *data, options_infos_t *options_infos)
{
    if (sfFloatRect_contains(&options_infos->volume_up_infos,
    options_infos->mouse_pos.x, options_infos->mouse_pos.y) &&
        data->volume + 5 < 100) {
        data->volume += 5;
        sfSleep(sfSeconds(0.5f));
    }
    if (sfFloatRect_contains(&options_infos->volume_down_infos,
    options_infos->mouse_pos.x, options_infos->mouse_pos.y) &&
    data->volume - 5 > 0) {
        data->volume -= 5;
        sfSleep(sfSeconds(0.5f));
    }
}

static void detect_button_mouse_click(data_t *data,
    options_infos_t *options_infos)
{
    if (sfFloatRect_contains(&options_infos->fullscreen_infos,
    options_infos->mouse_pos.x, options_infos->mouse_pos.y)) {
        if (!data->arguments.full_screen)
            toggle_fullscreen(data);
        else
            disable_fullscreen(data);
        sfRenderWindow_setFramerateLimit(data->window, GAME_FPS);
        data->screen_size = sfRenderWindow_getSize(data->window);
    }
    detect_volume_click(data, options_infos);
}

static void handle_button_clicks(data_t *data)
{
    options_infos_t options_infos = {{0, 0, 0, 0}, {0, 0, 0, 0},
        {0, 0, 0, 0}, {0, 0}};

    options_infos.mouse_pos =
    sfMouse_getPositionRenderWindow(data->window);
    options_infos.fullscreen_infos =
    sfSprite_getGlobalBounds(data->sprites.menu.options_sprites.full_screen);
    options_infos.volume_up_infos =
    sfSprite_getGlobalBounds(data->sprites.menu.options_sprites.volume_up);
    options_infos.volume_down_infos =
    sfSprite_getGlobalBounds(data->sprites.menu.options_sprites.volume_down);
    detect_button_mouse_click(data, &options_infos);
}

void handle_options_interactions(data_t *data)
{
    if (data->event.mouseButton.button == sfMouseLeft)
        handle_button_clicks(data);
}
