/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** load_sound
*/

#include "wolf3d.h"

static void create_new_struct(data_t *data, char *asset_path, char *asset_name)
{
    sound_t *new_struct = NULL;

    mini_printf("    loading %s as a new sound.\n", asset_path);
    new_struct = malloc(sizeof(sound_t));
    if (new_struct == NULL)
        return;
    new_struct->next = data->assets.sounds;
    new_struct->sound = sfSoundBuffer_createFromFile(asset_path);
    new_struct->name = my_strdup(asset_name);
    data->assets.sounds = new_struct;
}

static void overwrite_struct(data_t *data, char *asset_path,
    sound_t *asset_struct)
{
    mini_printf("    loading %s by overwriting the previous sound.\n",
        asset_path);
    sfSoundBuffer_destroy(asset_struct->sound);
    asset_struct->sound = sfSoundBuffer_createFromFile(asset_path);
}

//loads the asset by first checking for an asset with
//the same name to overwrite it
//if not found, creates a new asset struct
void load_sound(data_t *data, char *folder_path, char *asset_name)
{
    char asset_path[my_strlen(folder_path) + my_strlen(asset_name)];
    sound_t *asset_struct = data->assets.sounds;

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
