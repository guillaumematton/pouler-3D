/*
** EPITECH PROJECT, 2025
** save_data
** File description:
** save the data
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

void save_data(data_t *data)
{
    FILE *file = fopen("save.dat", "w");

    if (!file)
        return;
    fprintf(file, "%f\n", data->player.health);
    fprintf(file, "%f\n", data->player.x);
    fprintf(file, "%f\n", data->player.y);
    fprintf(file, "%f\n", data->player.dirX);
    fprintf(file, "%f\n", data->player.dirY);
    fprintf(file, "%f\n", data->player.planeX);
    fprintf(file, "%f\n", data->player.planeY);
    fprintf(file, "%s\n", data->map.current_map->name ?
    data->map.current_map->name : "NULL");
    save_weapons(data, file);
    fclose(file);
}
