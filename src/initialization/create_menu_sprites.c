/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** create_main_menu_sprites
*/

#include "wolf3d.h"

static void set_position_and_scale(float scale_value, float positionx,
    float positiony, sfSprite *sprite)
{
    sfVector2f scale = {scale_value, scale_value};
    sfVector2f position = {positionx, positiony};

    sfSprite_setPosition(sprite, position);
    sfSprite_setScale(sprite, scale);
    return;
}

static void set_sprite_positions(data_t *data)
{
    set_position_and_scale(1.38, 0, 0, data->sprites.menu.background);
    set_position_and_scale(0.5, 250, 175, data->sprites.menu.new_game);
    set_position_and_scale(0.375, 290, 260, data->sprites.menu.continue_game);
    set_position_and_scale(0.45, 290, 290, data->sprites.menu.options);
    set_position_and_scale(0.425, 300, 355, data->sprites.menu.lore);
    set_position_and_scale(0.3, 315, 460, data->sprites.menu.exit_game);
    set_position_and_scale(0.8, 0, 0, data->sprites.menu.title);
    return;
}

static bool create_gui_sprite(data_t *data, const char *filename,
    sfSprite **adress_sprite)
{
    gui_texture_t **gui_txt = &data->assets.gui_textures;
    gui_texture_t *gui = *gui_txt;
    sfSprite *sprite = sfSprite_create();

    if (!sprite)
        return true;
    for (; gui != NULL && my_strcmp(gui->name, filename) != 0;
        gui = gui->next);
    if (gui == NULL) {
        if (data->arguments.debug)
            printf("Failed to load %s sprite. Aborting\n", filename);
        sfSprite_destroy(sprite);
        return true;
    }
    sfSprite_setTexture(sprite, gui->texture, sfTrue);
    *adress_sprite = sprite;
    if (data->arguments.debug)
        printf("Loaded %s sprite.\n", filename);
    return false;
}

bool create_menu_sprites(data_t *data)
{
    if (create_gui_sprite(data, "menu_background.png",
        &data->sprites.menu.background) ||
    create_gui_sprite(data, "new_game.png", &data->sprites.menu.new_game) ||
    create_gui_sprite(data, "continue_game.png",
        &data->sprites.menu.continue_game) ||
    create_gui_sprite(data, "lore.png", &data->sprites.menu.lore) ||
    create_gui_sprite(data, "exit.png", &data->sprites.menu.exit_game) ||
    create_gui_sprite(data, "option.png", &data->sprites.menu.options) ||
    create_gui_sprite(data, "title.png", &data->sprites.menu.title) ||
    create_gui_sprite(data, "empty_box.png",
        &data->sprites.menu.options_sprites.empty_box) ||
    create_gui_sprite(data, "full_screen.png",
        &data->sprites.menu.options_sprites.full_screen) ||
    create_gui_sprite(data, "full_box.png",
        &data->sprites.menu.options_sprites.full_box) ||
    create_gui_sprite(data, "back.png",
        &data->sprites.menu.options_sprites.back))
        return true;
    set_sprite_positions(data);
    return false;
}
