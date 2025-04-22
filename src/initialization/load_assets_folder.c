/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** load_assets_folder
*/

#include "wolf3d.h"

void load_assets_folder(data_t *data, char *module_path, char *folder_name,
    void (*load_asset)(data_t *data, char *folder_path, char *asset_name))
{
    char folder_path[my_strlen(module_path) + my_strlen(folder_name)];
    DIR *dir = NULL;
    struct dirent *file = NULL;

    my_strcpy(folder_path, module_path);
    my_strcpy(folder_path + my_strlen(module_path), folder_name);
    dir = opendir(folder_path);
    if (dir == NULL)
        return;
    file = readdir(dir);
    while (file != NULL) {
        if (file->d_type == DT_REG)
            load_asset(data, folder_path, file->d_name);
        file = readdir(dir);
    }
    closedir(dir);
}
