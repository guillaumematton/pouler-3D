/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** load_data
*/

#include "wolf3d.h"

//loads all the assets from the module
//returns true if error
static bool load_module(data_t *data, char *name)
{
    char file_path[9 + 256] = "assets/";

    my_strcpy(file_path + 9, name);
    mini_printf("loading %s module.\n", name);
    //TODO
    //load_effects(data, file_path);
    //load_musics(data, file_path);
    //....... etc
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
//returns true if error
bool load_data(data_t *data)
{
    load_module(data, "core");
    load_modules(data);
}
