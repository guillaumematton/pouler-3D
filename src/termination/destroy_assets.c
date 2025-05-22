/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** destroy_assets
*/

#include "wolf3d.h"

static void destroy_sounds(data_t *data)
{
    sound_t *asset_struct = data->assets.sounds;
    sound_t *struct_to_free = NULL;

    while (asset_struct != NULL) {
        if (data->arguments.debug)
            mini_printf("    destroying %s.\n", asset_struct->name);
        sfSoundBuffer_destroy(asset_struct->sound);
        my_free(asset_struct->name);
        struct_to_free = asset_struct;
        asset_struct = asset_struct->next;
        free(struct_to_free);
    }
}

static void destroy_musics(data_t *data)
{
    music_t *asset_struct = data->assets.musics;
    music_t *struct_to_free = NULL;

    while (asset_struct != NULL) {
        if (data->arguments.debug)
            mini_printf("    destroying %s.\n", asset_struct->name);
        sfMusic_destroy(asset_struct->music);
        my_free(asset_struct->name);
        struct_to_free = asset_struct;
        asset_struct = asset_struct->next;
        free(struct_to_free);
    }
}

static void destroy_enemy_types(data_t *data)
{
    enemy_type_t *asset_struct = data->assets.enemy_types;
    enemy_type_t *struct_to_free = NULL;

    while (asset_struct != NULL) {
        if (data->arguments.debug)
            mini_printf("    destroying %s.\n", asset_struct->name);
        //TODO free stuff
        my_free(asset_struct->name);
        struct_to_free = asset_struct;
        asset_struct = asset_struct->next;
        free(struct_to_free);
    }
}

static void destroy_maps(data_t *data)
{
    map_t *asset_struct = data->assets.maps;
    map_t *struct_to_free = NULL;

    while (asset_struct != NULL) {
        if (data->arguments.debug)
            mini_printf("    destroying %s.\n", asset_struct->name);
        my_free(asset_struct->name);
        my_freestrarray(asset_struct->walls);
        my_freestrarray(asset_struct->floor);
        my_freestrarray(asset_struct->ceiling);
        my_freestrarray(asset_struct->special);
        struct_to_free = asset_struct;
        asset_struct = asset_struct->next;
        free(struct_to_free);
    }
}

static void destroy_weapons(data_t *data)
{
    weapon_t *asset_struct = data->assets.weapons;
    weapon_t *struct_to_free = NULL;

    while (asset_struct != NULL) {
        if (data->arguments.debug)
            mini_printf("    destroying %s.\n", asset_struct->name);
        my_free(asset_struct->name);
        struct_to_free = asset_struct;
        asset_struct = asset_struct->next;
        free(struct_to_free);
    }
}

static void destroy_entity_textures(data_t *data)
{
    entity_texture_t *asset_struct = data->assets.entity_textures;
    entity_texture_t *struct_to_free = NULL;

    while (asset_struct != NULL) {
        if (data->arguments.debug)
            mini_printf("    destroying %s.\n", asset_struct->name);
        sfTexture_destroy(asset_struct->texture);
        my_free(asset_struct->name);
        struct_to_free = asset_struct;
        asset_struct = asset_struct->next;
        free(struct_to_free);
    }
}

static void destroy_environment_textures(data_t *data)
{
    environment_texture_t *asset_struct = data->assets.environment_textures;
    environment_texture_t *struct_to_free = NULL;

    while (asset_struct != NULL) {
        if (data->arguments.debug)
            mini_printf("    destroying %s.\n", asset_struct->name);
        sfTexture_destroy(asset_struct->texture);
        my_free(asset_struct->name);
        struct_to_free = asset_struct;
        asset_struct = asset_struct->next;
        free(struct_to_free);
    }
}

static void destroy_gui_textures(data_t *data)
{
    gui_texture_t *asset_struct = data->assets.gui_textures;
    gui_texture_t *struct_to_free = NULL;

    while (asset_struct != NULL) {
        if (data->arguments.debug)
            mini_printf("    destroying %s.\n", asset_struct->name);
        sfTexture_destroy(asset_struct->texture);
        my_free(asset_struct->name);
        struct_to_free = asset_struct;
        asset_struct = asset_struct->next;
        free(struct_to_free);
    }
}

void destroy_assets(data_t *data)
{
    if (data->arguments.debug)
        mini_printf("  destroying assets.\n");
    destroy_sounds(data);
    destroy_musics(data);
    destroy_enemy_types(data);
    destroy_maps(data);
    destroy_weapons(data);
    destroy_entity_textures(data);
    destroy_environment_textures(data);
    destroy_gui_textures(data);
}
