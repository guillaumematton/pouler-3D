/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** load_gui_texture
*/

#include "wolf3d.h"

static void create_new_struct(data_t *data, char *asset_path, char *asset_name)
{
    gui_texture_t *new_struct = NULL;

    if (data->arguments.debug)
        mini_printf(
        "\tloading %s as a new gui texture.\n",
        asset_path);
    new_struct = malloc(sizeof(gui_texture_t));
    if (new_struct == NULL)
        return;
    new_struct->next = data->assets.gui_textures;
    new_struct->texture = sfTexture_createFromFile(asset_path, NULL);
    new_struct->name = my_strdup(asset_name);
    data->assets.gui_textures = new_struct;
}

static void overwrite_struct(data_t *data, char *asset_path,
    gui_texture_t *asset_struct)
{
    if (data->arguments.debug)
        mini_printf(
        "\tloading %s by overwriting the previous gui texture.\n",
        asset_path);
    sfTexture_destroy(asset_struct->texture);
    asset_struct->texture = sfTexture_createFromFile(asset_path, NULL);
}

//loads the asset by first checking for an asset with
//the same name to overwrite it
//if not found, creates a new asset struct
void load_gui_texture(data_t *data, char *folder_path, char *asset_name)
{
    char asset_path[my_strlen(folder_path) + my_strlen(asset_name)];
    gui_texture_t *asset_struct = data->assets.gui_textures;

    my_strcpy(asset_path, folder_path);
    my_strcpy(asset_path + my_strlen(folder_path), asset_name);
    while (asset_struct != NULL) {
        if (my_strcmp(asset_struct->name, asset_name) == 0) {
            overwrite_struct(data, asset_path, asset_struct);
            return;
        }
        asset_struct = asset_struct->next;
    }
    create_new_struct(data, asset_path, asset_name);
}
