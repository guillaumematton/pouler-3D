/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** load_weapon
*/

#include "wolf3d.h"

static void weapon_parser(char *asset_path, weapon_t *asset_struct)
{
    char *buffer = my_readfile(asset_path);
    char **lines = my_strsplit(buffer, "\n", false);

    if (buffer == NULL || lines == NULL)
        return;
    if (my_ptrarraylen((void **) lines) >= 6) {
        asset_struct->damage = atoi(lines[0]);
        asset_struct->max_ammo = atoi(lines[1]);
        asset_struct->ammo = atoi(lines[2]);
        asset_struct->firerate = atoi(lines[3]);
        asset_struct->explosive = lines[4][0] == '1';
        asset_struct->melee = lines[5][0] == '1';
    }
    free(buffer);
    my_freestrarray(lines);
}

static void create_new_struct(data_t *data, char *asset_path,
    char *asset_name, weapon_t **adress)
{
    weapon_t *new_struct = NULL;

    if (data->arguments.debug)
        mini_printf(
        "\tloading %s as a new weapon.\n",
        asset_path);
    new_struct = malloc(sizeof(weapon_t));
    if (new_struct == NULL)
        return;
    new_struct->next = *adress;
    weapon_parser(asset_path, new_struct);
    new_struct->name = my_strdup(asset_name);
    *adress = new_struct;
}

static void overwrite_struct(data_t *data, char *asset_path,
    weapon_t *asset_struct)
{
    if (data->arguments.debug)
        mini_printf(
        "\tloading %s by overwriting the previous weapon.\n",
        asset_path);
    weapon_parser(asset_path, asset_struct);
}

//loads the asset by first checking for an asset with
//the same name to overwrite it
//if not found, creates a new asset struct
void load_weapon(data_t *data, char *folder_path, char *asset_name)
{
    char asset_path[my_strlen(folder_path) + my_strlen(asset_name)];
    weapon_t *asset_struct = data->assets.weapons;

    my_strcpy(asset_path, folder_path);
    my_strcpy(asset_path + my_strlen(folder_path), asset_name);
    while (asset_struct != NULL) {
        if (my_strcmp(asset_struct->name, asset_name) == 0) {
            overwrite_struct(data, asset_path, asset_struct);
            return;
        }
        asset_struct = asset_struct->next;
    }
    create_new_struct(data, asset_path, asset_name, &data->assets.weapons);
}
