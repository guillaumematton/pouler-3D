/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** load_map
*/

#include "wolf3d.h"

static void create_new_struct(data_t *data, char *asset_path, char *asset_name)
{
    map_t *new_struct = NULL;

    mini_printf("loading %s as a new map.\n", asset_path);
    new_struct = malloc(sizeof(map_t));
    if (new_struct == NULL)
        return;
    new_struct->next = data->assets.maps;
    //TODO parser
    new_struct->name = my_strdup(asset_name);
    data->assets.maps = new_struct;
}

static void overwrite_struct(data_t *data, char *asset_path,
    map_t *asset_struct)
{
    mini_printf("loading %s by overwriting the previous map.\n", asset_path);
    //TODO parser
}

//loads the asset by first checking for an asset with
//the same name to overwrite it
//if not found, creates a new asset struct
void load_map(data_t *data, char *folder_path, char *asset_name)
{
    char asset_path[my_strlen(folder_path) + my_strlen(asset_name)];
    map_t *asset_struct = data->assets.maps;

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
