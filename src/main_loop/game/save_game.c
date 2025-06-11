/*
** EPITECH PROJECT, 2025
** save_game
** File description:
** save the game
*/

#include "wolf3d.h"

static void save_weapons(data_t *data, FILE *file)
{
    const weapon_t *temp = data->current_weapon.weapon;

    while (temp) {
        fprintf(file, "%s\n", temp->name ? temp->name : "NULL");
        fprintf(file, "%f\n", temp->damage);
        fprintf(file, "%d\n", temp->ammo);
        fprintf(file, "%d\n", temp->max_ammo);
        fprintf(file, "%f\n", temp->firerate);
        fprintf(file, "%d\n", temp->explosive ? 1 : 0);
        fprintf(file, "%d\n", temp->melee ? 1 : 0);
        temp = temp->next;
    }
}

static void save_player_data(data_t *data, FILE *file)
{
    fprintf(file, "%f\n", data->player.health);
    fprintf(file, "%f\n", data->player.x);
    fprintf(file, "%f\n", data->player.y);
    fprintf(file, "%f\n", data->player.dirX);
    fprintf(file, "%f\n", data->player.dirY);
    fprintf(file, "%f\n", data->player.planeX);
    fprintf(file, "%f\n", data->player.planeY);
    fprintf(file, "%s\n", data->map.current_map->name ?
    data->map.current_map->name : "NULL");
}

void save_game(data_t *data)
{
    FILE *file = fopen("save.dat", "w");

    if (data->arguments.debug)
        my_putstr("saving the game.\n");
    if (!file) {
        if (data->arguments.debug)
            my_putstr("  failed to save.\n");
        return;
    }
    save_player_data(data, file);
    save_weapons(data, file);
    fclose(file);
    if (data->arguments.debug)
        my_putstr("  succesfully saved.\n");
}
