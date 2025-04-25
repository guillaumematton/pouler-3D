/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** create_main_menu_sprites
*/

#include "wolf3d.h"

bool create_gui_sprite(data_t *data, const char *filename, sfSprite *sprite)
{
    gui_texture_t **gui_txt = &data->assets.gui_textures;
    gui_texture_t *gui = *gui_txt;

    sprite = sfSprite_create();
    if (!sprite)
        return true;
    for (; gui != NULL && my_strcmp(gui->name, filename) != 0;
        gui = gui->next);
    if (gui == NULL)
        return true;
    sfSprite_setTexture(sprite, gui->texture, sfTrue);
    return false;
}

bool create_options_sprite(data_t *data)
{
    if (create_gui_sprite(data, "empty_box.png",
        data->sprites.menu.options_sprites.empty_box))
        return true;
    if (create_gui_sprite(data, "full_screen.png",
        data->sprites.menu.options_sprites.full_screen))
        return true;
    return false;
}

bool create_menu_sprites(data_t *data)
{
    if (create_gui_sprite(data, "menu_background.png",
        data->sprites.menu.background))
        return true;
    if (create_gui_sprite(data, "start_game.png",
        data->sprites.menu.start_game))
        return true;
    if (create_gui_sprite(data, "lore.png", data->sprites.menu.lore))
        return true;
    if (create_gui_sprite(data, "option.png", data->sprites.menu.options))
        return true;
    if (create_options_sprite(data))
        return true;
    return false;
}
