/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** create_main_menu_sprites
*/

#include "wolf3d.h"

bool create_menu_background(data_t *data)
{
    gui_texture_t **gui_txt = &data->assets.gui_textures;
    gui_texture_t *gui = *gui_txt;

    data->sprites.menu->background = sfSprite_create();
    if (!data->sprites.menu->background)
        return true;
    for (; gui != NULL && my_strcmp(gui->name, "menu_background.png") != 0;
        gui = gui->next);
    if (gui == NULL) {
        sfSprite_destroy(data->sprites.menu->background);
        return true;
    }
    printf("Sprite exist\n");
    sfSprite_setTexture(data->sprites.menu->background, gui->texture, sfTrue);
    sfSprite_setScale(data->sprites.menu->background, (sfVector2f){1.379310345, 1.392111369});
    sfSprite_setPosition(data->sprites.menu->background, (sfVector2f){0, 0});
    sfRenderWindow_drawSprite(data->window, data->sprites.menu->background, NULL);
    return false;
}
