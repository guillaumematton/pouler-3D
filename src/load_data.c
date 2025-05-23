/*
** EPITECH PROJECT, 2025
** load_data.c
** File description:
** load the data
*/

#include "wolf3d.h"

static char *read_line(FILE *file)
{
    char buffer[256];
    size_t len = 0;

    if (!fgets(buffer, sizeof(buffer), file))
        return NULL;
    len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n')
        buffer[len - 1] = '\0';
    return strdup(buffer);
}

static weapon_t *load_weapons(FILE *file)
{
    weapon_t *head = NULL;
    weapon_t *current = NULL;
    weapon_t *new_weapon = NULL;
    char *name = NULL;
    int temp_explosive = 0;
    int temp_melee = 0;

    while (1) {
        name = read_line(file);
        if (!name)
            break;
        new_weapon = malloc(sizeof(weapon_t));
        new_weapon->name = strcmp(name, "NULL") == 0 ? NULL : name;
        if (fscanf(file, "%f\n", &new_weapon->damage) != 1)
            break;
        if (fscanf(file, "%d\n", &new_weapon->ammo) != 1)
            break;
        if (fscanf(file, "%d\n", &new_weapon->max_ammo) != 1)
            break;
        if (fscanf(file, "%f\n", &new_weapon->firerate) != 1)
            break;
        if (fscanf(file, "%d\n", &temp_explosive) != 1)
            break;
        if (fscanf(file, "%d\n", &temp_melee) != 1)
            break;
        new_weapon->explosive = temp_explosive;
        new_weapon->melee = temp_melee;
        new_weapon->next = NULL;
        if (!head)
            head = new_weapon;
        else
            current->next = new_weapon;
        current = new_weapon;
    }
    return head;
}

void load_data(data_t *data)
{
    FILE *file = fopen("save.dat", "r");
    char *map_name = NULL;

    if (!file)
        return;
    fscanf(file, "%f\n", &data->player.health);
    fscanf(file, "%f\n", &data->player.x);
    fscanf(file, "%f\n", &data->player.y);
    fscanf(file, "%f\n", &data->player.dirX);
    fscanf(file, "%f\n", &data->player.dirY);
    fscanf(file, "%f\n", &data->player.planeX);
    fscanf(file, "%f\n", &data->player.planeY);
    map_name = read_line(file);
    if (map_name && strcmp(map_name, "NULL") != 0) {
        data->map.current_map = malloc(sizeof(map_t));
        data->map.current_map->name = map_name;
    } else {
        free(map_name);
        data->map.current_map = NULL;
    }
    data->current_weapon.weapon = load_weapons(file);
    fclose(file);
}
