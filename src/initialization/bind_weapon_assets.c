/*
** EPITECH PROJECT, 2025
** wolf3d.h
** File description:
** bind_weapon_assets
*/

#include "wolf3d.h"

static void find_weapon_texture(data_t *data, weapon_t *weapon)
{
    gui_texture_t *texture = data->assets.gui_textures;

    weapon->texture = NULL;
    for (; texture != NULL; texture = texture->next) {
        if (my_strncmp(weapon->name, texture->name,
            my_strlen(weapon->name) - 4) == 0) {
            weapon->texture = texture->texture;
            break;
        }
    }
    if (data->arguments.debug && weapon->texture != NULL)
        printf("\t%s.\n", texture->name);
}

static void create_weapon_sprite(weapon_t *weapon)
{
    weapon->sprite = NULL;
    if (weapon->texture != NULL) {
        weapon->sprite = sfSprite_create();
        if (weapon->sprite != NULL) {
            sfSprite_setTexture(weapon->sprite, weapon->texture, false);
        }
    }
}

static void find_weapon_sound(data_t *data, weapon_t *weapon)
{
    sound_t *sound = data->assets.sounds;

    weapon->sound = NULL;
    for (; sound != NULL; sound = sound->next) {
        if (my_strncmp(weapon->name, sound->name,
            my_strlen(weapon->name) - 4) == 0) {
            weapon->sound = sound->sound;
            break;
        }
    }
    if (data->arguments.debug && weapon->sound != NULL)
        printf("\t%s.\n", sound->name);
}

void bind_weapon_assets(data_t *data)
{
    weapon_t *weapon = data->assets.weapons;

    if (data->arguments.debug)
        my_putstr("    binding weapons assets.\n");
    for (; weapon != NULL; weapon = weapon->next) {
        if (data->arguments.debug)
            mini_printf("      binding %s with:\n", weapon->name);
        find_weapon_texture(data, weapon);
        create_weapon_sprite(weapon);
        find_weapon_sound(data, weapon);
    }
}
