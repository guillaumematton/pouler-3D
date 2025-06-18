/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** load_game
*/

#include "wolf3d.h"

static void load_player_data(data_t *data, char **lines)
{
    printf("  map is %s.\n", lines[7]);
    set_new_map(data, lines[7]);
    data->player.health = atof(lines[0]);
    data->player.x = atof(lines[1]);
    data->player.y = atof(lines[2]);
    data->player.dirX = atof(lines[3]);
    data->player.dirY = atof(lines[4]);
    data->player.planeX = atof(lines[5]);
    data->player.planeY = atof(lines[6]);
    data->score = atoi(lines[8]);
    data->game_time = atof(lines[9]);
}

static void set_weapon_ammo(data_t *data, char *name, char *ammo_str)
{
    if (name == NULL || ammo_str == NULL)
        return;
    printf("  loading weapon %s with %i ammo.\n", name, atoi(ammo_str));
    for (weapon_t *weapon = data->assets.weapons;
        weapon != NULL; weapon = weapon->next) {
        if (my_strcmp(name, weapon->name) == 0) {
            weapon->ammo = atoi(ammo_str);
            return;
        }
    }
}

static void load_weapons_ammo(data_t *data, char **lines)
{
    for (int i = 11; i < my_ptrarraylen((void **) lines); i += 7) {
        set_weapon_ammo(data, lines[i - 2], lines[i]);
    }
}

void load_game(data_t *data)
{
    char *buffer = my_readfile("save.dat");
    char **lines = my_strsplit(buffer, "\n", false);

    if (data->arguments.debug)
        my_putstr("loading a save.\n");
    if (buffer == NULL || lines == NULL ||
        my_ptrarraylen((void **) lines) < 10) {
        my_free(buffer);
        my_freestrarray(lines);
        if (data->arguments.debug)
            my_putstr("  failed to load the game save.\n");
        return;
    }
    load_player_data(data, lines);
    load_weapons_ammo(data, lines);
    my_free(buffer);
    my_freestrarray(lines);
}
