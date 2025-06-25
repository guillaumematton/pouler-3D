/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** create_main_menu_sprites
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

void set_sprite_positions(data_t *data)
{
    if (!data->arguments.full_screen) {
        set_position_scale(1.38, 0, 0, data->sprites.menu.background);
        set_position_scale(0.5, 285, 255, data->sprites.menu.new_game);
        set_position_scale(0.375, 300, 320, data->sprites.menu.continue_game);
        set_position_scale(0.35, 325, 375, data->sprites.menu.options);
        set_position_scale(0.425, 340, 435, data->sprites.menu.lore);
        set_position_scale(0.3, 347, 500, data->sprites.menu.exit_game);
        set_position_scale(0.8, 0, 0, data->sprites.menu.title);
    } else {
        set_position_scale(3.5, 0, 0, data->sprites.menu.background);
        set_position_scale(1, 800, 450, data->sprites.menu.new_game);
        set_position_scale(0.7, 850, 570, data->sprites.menu.continue_game);
        set_position_scale(0.7, 875, 675, data->sprites.menu.options);
        set_position_scale(0.85, 900, 825, data->sprites.menu.lore);
        set_position_scale(0.6, 915, 950, data->sprites.menu.exit_game);
        set_position_scale(1.6, 150, 0, data->sprites.menu.title);
    }
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

bool create_options_sprites(data_t *data)
{
    if (create_gui_sprite(data, "full_screen.png",
        &data->sprites.menu.options_sprites.full_screen) ||
    create_gui_sprite(data, "back.png",
        &data->sprites.menu.options_sprites.back) ||
    create_gui_sprite(data, "pause_background.jpg",
    &data->sprites.menu.p_background) ||
    create_gui_sprite(data, "options_background.jpg",
    &data->sprites.menu.o_background) ||
        create_gui_sprite(data, "volume.png",
    &data->sprites.menu.options_sprites.volume) ||
        create_gui_sprite(data, "volume_up.png",
    &data->sprites.menu.options_sprites.volume_up) ||
        create_gui_sprite(data, "volume_down.png",
    &data->sprites.menu.options_sprites.volume_down) ||
        create_gui_sprite(data, "save.png",
    &data->sprites.menu.options_sprites.save))
        return true;
    return false;
}

bool create_lore_sprites(data_t *data)
{
    if (create_gui_sprite(data, "lore1.png",
        &data->sprites.menu.lore_sprites.lore1) ||
    create_gui_sprite(data, "lore2.png",
        &data->sprites.menu.lore_sprites.lore2) ||
    create_gui_sprite(data, "lore3.png",
        &data->sprites.menu.lore_sprites.lore3) ||
    create_gui_sprite(data, "lore4.png",
        &data->sprites.menu.lore_sprites.lore4) ||
    create_gui_sprite(data, "lore5.png",
    &data->sprites.menu.lore_sprites.lore5) ||
    create_gui_sprite(data, "lore6.png",
    &data->sprites.menu.lore_sprites.lore6) ||
        create_gui_sprite(data, "lore7.png",
    &data->sprites.menu.lore_sprites.lore7) ||
        create_gui_sprite(data, "lore8.png",
    &data->sprites.menu.lore_sprites.lore8) ||
        create_gui_sprite(data, "lore9.png",
    &data->sprites.menu.lore_sprites.lore9))
        return true;
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
    create_gui_sprite(data, "options.png", &data->sprites.menu.options) ||
    create_gui_sprite(data, "title.png", &data->sprites.menu.title) ||
        create_options_sprites(data) || create_lore_sprites(data) ||
    create_gui_sprite(data, "win_screen_background.png",
        &data->sprites.win_screen.background))
        return true;
    set_sprite_positions(data);
    return false;
}
