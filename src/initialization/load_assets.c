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
    char module_path[8 + 256] = "assets/";

    my_strcpy(module_path + 7, name);
    mini_printf("loading %s module.\n", name);
    load_assets_folder(data, module_path, "/audio/sounds/", &load_sound);
    load_assets_folder(data, module_path, "/audio/musics/", &load_music);
    load_assets_folder(data, module_path, "/audio/enemy_types/",
        &load_enemy_type);
    load_assets_folder(data, module_path, "/audio/maps/", &load_map);
    load_assets_folder(data, module_path, "/audio/weapons/", &load_weapon);
    load_assets_folder(data, module_path, "/audio/entity_textures/",
        &load_entity_texture);
    load_assets_folder(data, module_path, "/audio/environment_texture/",
        &load_environment_texture);
    load_assets_folder(data, module_path, "/audio/gui_texture/",
        &load_gui_texture);
    //(and the logic in case of loading failure)
}

//loads all modules execpt core
//returns true if error
static bool load_modules(data_t *data)
{
    DIR *dir = opendir("assets");
    struct dirent *file = NULL;
    bool status = false;

    if (dir == NULL) {
        return 84;
    }
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
}

//load all the assets, staring by the "core" module
//then the other (if any) so they can override core's assets
//returns true if error
bool load_assets(data_t *data)
{
    load_module(data, "core");
    load_modules(data);
}
