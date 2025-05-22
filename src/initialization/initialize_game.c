/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** initialize_game
*/

#include "wolf3d.h"

//returns true if error
static bool set_window(data_t *data)
{
    sfVideoMode mode = {800, 600, 32};
    int arg = sfClose;

    data->clock = sfClock_create();
    if (!data->clock)
        return true;
    if (data->arguments.full_screen) {
        arg = sfClose | sfFullscreen;
        mode.width = 1920;
        mode.height = 1080;
    }
    data->window = sfRenderWindow_create(mode, "wolf3D",
        arg, NULL);
    if (!data->window)
        return true;
    sfRenderWindow_setFramerateLimit(data->window, GAME_FPS);
    data->screen_size = sfRenderWindow_getSize(data->window);
    return false;
}

static void initialize_player(data_t *data)
{
    data->player.health = 100;
    data->player.x = 2;
    data->player.y = 2;
    data->player.dirX = 1;
    data->player.dirY = 0;
    data->player.planeX = 0;
    data->player.planeY = 0.9;
}

//returns true if error
static bool set_text(data_t *data)
{
    font_t *font = data->assets.fonts;

    data->hud_text = sfText_create();
    if (data->hud_text == NULL)
        return true;
    for (; font != NULL; font = font->next) {
        if (my_strncmp("hud", font->name, 3) == 0) {
            sfText_setFont(data->hud_text, font->font);
            sfText_setPosition(data->hud_text,
                (sfVector2f) {10, 10});
            return false;
        }
    }
    return true;
}

//does all the neccessary work to start the game (which you just lost)
//returns true if error
bool initialize_game(data_t *data)
{
    if (data->arguments.debug)
        mini_printf("starting game initialization.\n");
    srand(time(NULL));
    data->game_vertex = sfVertexArray_create();
    if (!data->game_vertex)
        return true;
    sfVertexArray_setPrimitiveType(data->game_vertex, sfPoints);
    if (set_window(data))
        return true;
    initialize_player(data);
    if (load_assets(data))
        return true;
    if (set_text(data))
        return true;
    bind_assets(data);
    if (create_menu_sprites(data) || create_wall_images(data))
        return true;
    set_sprite_positions(data);
    return false;
}
