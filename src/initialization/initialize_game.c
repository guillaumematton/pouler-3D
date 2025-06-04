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
    data->window = sfRenderWindow_create(mode, "P.O.U.L.E.R 3.D",
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

bool initialize_rendering_tools(data_t *data)
{
    data->game_screen_text = sfTexture_create(INTERNAL_WIDTH, INTERNAL_HEIGHT);
    if (!data->game_screen_text) {
        printf("Error: Could not create game screen texture. Aborting...\n");
        return true;
    }
    data->game_screen = sfSprite_create();
    if (!data->game_screen) {
        printf("Error: Could not create game screen sprite. Aborting...\n");
        return true;
    }
    data->game_screen_image = sfImage_create(INTERNAL_WIDTH, INTERNAL_HEIGHT);
    if (!data->game_screen_image) {
        printf("Error: Could not create game screen image. Aborting...\n");
        return true;
    }
    return false;
}

//does all the neccessary work to start the game (which you just lost)
//returns true if error
bool initialize_game(data_t *data)
{
    if (data->arguments.debug)
        mini_printf("starting game initialization.\n");
    srand(time(NULL));
    if (initialize_rendering_tools(data))
        return true;
    if (set_window(data))
        return true;
    initialize_player(data);
    if (load_assets(data))
        return true;
    if (set_text(data) || bind_assets(data))
        return true;
    if (create_menu_sprites(data) || create_wall_images(data))
        return true;
    set_sprite_positions(data);
    return false;
}
