/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** load_assets
*/

#include "wolf3d.h"

//loads all the assets from the module
//(TODO; will) returns true if error
static bool load_module(data_t *data, char *name)
{
    char module_path[8 + my_strlen(name)];

    my_strcpy(module_path, "assets/");
    my_strcpy(module_path + 7, name);
    if (data->arguments.debug)
        mini_printf("    loading %s module.\n", name);
    load_assets_folder(data, module_path, "/audio/sounds/", &load_sound);
    load_assets_folder(data, module_path, "/audio/musics/", &load_music);
    load_assets_folder(data, module_path, "/data/enemy_types/",
        &load_enemy_type);
    load_assets_folder(data, module_path, "/data/levels/", &load_map);
    load_assets_folder(data, module_path, "/data/weapons/", &load_weapon);
    load_assets_folder(data, module_path, "/textures/entities/",
        &load_entity_texture);
    load_assets_folder(data, module_path, "/textures/environment/",
        &load_environment_texture);
    load_assets_folder(data, module_path, "/textures/gui/",
        &load_gui_texture);
    load_assets_folder(data, module_path, "/fonts/", &load_font);
    return false;
}

//loads all modules execpt core
//returns true if error
static bool load_modules(data_t *data)
{
    DIR *dir = opendir("assets");
    struct dirent *file = NULL;
    bool status = false;

    if (dir == NULL)
        return true;
    file = readdir(dir);
    while (file != NULL) {
        if (status == true)
            return true;
        if (file->d_type == DT_DIR &&
            file->d_name[0] != '.' &&
            my_strcmp(file->d_name, "core") != 0) {
            status = load_module(data, file->d_name);
        }
        file = readdir(dir);
    }
    closedir(dir);
    return false;
}

//load all the assets, staring by the "core" module
//then the other (if any) so they can override core's assets
//returns true if error
bool load_assets(data_t *data)
{
    data->tile = sfRectangleShape_create();
    if (!data->tile) {
        my_putstr("Error: could not create tile rectangle shape"
            " for minimap. Aborting...\n");
        return true;
    }
    if (data->arguments.debug)
        mini_printf("  loading assets.\n");
    load_module(data, "core");
    load_modules(data);
    return false;
}
