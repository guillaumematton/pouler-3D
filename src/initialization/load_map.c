/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** load_map
*/

#include "wolf3d.h"

static char *create_empty_line(unsigned int len)
{
    char *str = malloc(len + 1);

    if (str == NULL)
        return NULL;
    for (unsigned int i = 0; i < len; i++)
        str[i] = ' ';
    str[len] = '\0';
    return str;
}

static char *copy_line(char *trg, unsigned int len)
{
    char *str = malloc(len + 1);

    if (str == NULL)
        return NULL;
    for (unsigned int i = 0; i < len; i++)
        str[i] = ' ';
    str[len] = '\0';
    my_strncpy(str, trg, len);
    return str;
}

static void parse_array(char **lines, char ***array, map_t *asset_struct)
{
    bool failed = false;

    *array = malloc(sizeof(char *) * (asset_struct->y_size + 1));
    if (*array == NULL)
        return;
    (*array)[asset_struct->x_size] = NULL;
    for (unsigned int i = 0; i < asset_struct->y_size; i++) {
        if (failed == false && lines[i] == NULL)
            failed = true;
        if (failed) {
            (*array)[i] = create_empty_line(asset_struct->x_size);
        } else
            (*array)[i] = copy_line(lines[i], asset_struct->x_size);
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

static void map_parser(char *asset_path, map_t *asset_struct)
{
    char *buffer = my_readfile(asset_path);
    char **lines = my_strsplit(buffer, "\n", false);

    if (buffer == NULL || lines == NULL ||
        my_ptrarraylen((void **) lines) < 6) {
        my_free(buffer);
        my_freestrarray(lines);
        my_putstr("\t  failed to load the map.\n");
        return;
    }
    parse_size(lines[0], asset_struct);
    asset_struct->floor_texture_name = my_strdup(lines[1]);
    asset_struct->wall_texture_name = my_strdup(lines[2]);
    asset_struct->ceiling_texture_name = my_strdup(lines[3]);
    asset_struct->next_map_name = my_strdup(lines[4]);
    parse_array(lines + 5, &asset_struct->map, asset_struct);
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
    map_parser(asset_path, new_struct);
    new_struct->name = my_strdup(asset_name);
    data->assets.maps = new_struct;
}

static void overwrite_struct(data_t *data, char *asset_path,
    map_t *asset_struct)
{
    if (data->arguments.debug)
        mini_printf(
        "\tloading %s by overwriting the previous map.\n",
        asset_path);
    my_free(asset_struct->floor_texture_name);
    my_free(asset_struct->wall_texture_name);
    my_free(asset_struct->ceiling_texture_name);
    my_free(asset_struct->next_map_name);
    my_freestrarray(asset_struct->map);
    map_parser(asset_path, asset_struct);
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
