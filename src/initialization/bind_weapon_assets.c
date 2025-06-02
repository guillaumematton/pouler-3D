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

static bool create_weapon_sprite(weapon_t *weapon)
{
    weapon->default_sprite = NULL;
    if (weapon->texture != NULL) {
        weapon->default_sprite = sfSprite_create();
        if (!weapon->default_sprite) {
            my_putstr("Error: could not create weapon sprite. Aborting...\n");
            return true;
        }
        sfSprite_setTexture(weapon->default_sprite, weapon->texture, false);
    }
    return false;
}

static void find_weapon_sound(data_t *data, weapon_t *weapon)
{
    sound_t *sound = data->assets.sounds;

    weapon->sound = NULL;
    for (; sound != NULL; sound = sound->next) {
        if (my_strncmp(weapon->name, sound->name,
            my_strlen(weapon->name) - 4) == 0) {
            weapon->sound = sound;
            break;
        }
    }
    if (data->arguments.debug && weapon->sound != NULL)
        printf("\t%s.\n", sound->name);
}

bool split_weapon_spritesheet(weapon_t *weapon)
{
    sfVector2u size = {0, 0};

    if (weapon->texture == NULL || weapon->default_sprite == NULL)
        return false;
    size = sfTexture_getSize(weapon->texture);
    weapon->fire_sprite = sfSprite_create();
    if (!weapon->fire_sprite) {
        my_putstr("Error: could not create weapon fire sprite. Aborting...\n");
        return true;
    }
    sfSprite_setTexture(weapon->fire_sprite, weapon->texture, false);
    sfSprite_setTextureRect(weapon->fire_sprite,
        (sfIntRect) {size.x / 2, 0, size.x, size.y});
    sfSprite_setTextureRect(weapon->default_sprite,
        (sfIntRect) {0, 0, size.x / 2, size.y});
    return false;
}

bool bind_weapon_assets(data_t *data)
{
    weapon_t *weapon = data->assets.weapons;

    if (data->arguments.debug)
        my_putstr("    binding weapons assets.\n");
    for (; weapon != NULL; weapon = weapon->next) {
        if (data->arguments.debug)
            mini_printf("      binding %s with:\n", weapon->name);
        find_weapon_texture(data, weapon);
        if (create_weapon_sprite(weapon))
            return true;
        find_weapon_sound(data, weapon);
        split_weapon_spritesheet(weapon);
    }
    return false;
}
