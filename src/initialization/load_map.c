/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** load_map
*/

#include "wolf3d.h"

static void parse_array(char **lines, char ***array, map_t *asset_struct)
{
    *array = malloc(sizeof(char *) * (asset_struct->y_size + 1));
    if (*array == NULL)
        return;
    (*array)[asset_struct->x_size] = NULL;
    for (int i = 0; i < asset_struct->y_size; i++) {
        if (lines[i] == NULL) {
            (*array)[i] = NULL;
            return;
        }
        (*array)[i] = my_strndup(lines[i], asset_struct->x_size);
    }
}

static void parse_size(char *line, map_t *asset_struct)
{
    char **arr = my_strsplit(line, " ", false);

    if (arr == NULL || my_ptrarraylen((void *) arr) < 2)
        return;
    asset_struct->x_size = atoi(arr[0]);
    asset_struct->y_size = atoi(arr[1]);
    my_freestrarray(arr);
}

static void map_parser(char *asset_path, map_t *asset_struct, char *asset_name)
{
    char *buffer = my_readfile(asset_path);
    char **lines = my_strsplit(buffer, "\n", false);

    if (buffer == NULL || lines == NULL)
        return;
    asset_struct->name = my_strdup(asset_name);
    parse_size(lines[1], asset_struct);
    parse_array(lines + 2, &asset_struct->walls, asset_struct);
    parse_array(lines + 2 + asset_struct->y_size,
                &asset_struct->floor, asset_struct);
    parse_array(lines + 2 + asset_struct->y_size * 2,
                &asset_struct->ceiling, asset_struct);
    parse_array(lines + 2 + asset_struct->y_size * 3,
                &asset_struct->special, asset_struct);
    free(buffer);
    my_freestrarray(lines);
}

static void create_new_struct(data_t *data, char *asset_path, char *asset_name)
{
    map_t *new_struct = NULL;

    if (data->arguments.debug)
        mini_printf(
        "\tloading %s as a new map.\n",
        asset_path);
    new_struct = malloc(sizeof(map_t));
    if (new_struct == NULL)
        return;
    new_struct->next = data->assets.maps;
    map_parser(asset_path, new_struct, asset_name);
    new_struct->name = my_strdup(asset_name);
    data->assets.maps = new_struct;
}

static void overwrite_struct(data_t *data, char *asset_path,
    map_t *asset_struct, char *asset_name)
{
    if (data->arguments.debug)
        mini_printf(
        "\tloading %s by overwriting the previous map.\n",
        asset_path);
    my_free(asset_struct->name);
    my_freestrarray(asset_struct->walls);
    my_freestrarray(asset_struct->floor);
    my_freestrarray(asset_struct->ceiling);
    map_parser(asset_path, asset_struct, asset_name);
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
            overwrite_struct(data, asset_path, asset_struct, asset_name);
            return;
        }
        asset_struct = asset_struct->next;
    }
    create_new_struct(data, asset_path, asset_name);
}
