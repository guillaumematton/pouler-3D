/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** stop_csfml_simple
*/

#include "wolf3d.h"

/*void destroy_window_and_music(data_t *data)
{
    music_t *next_music = NULL;

    sfRenderWindow_close(data->window);
    sfRenderWindow_destroy(data->window);
    for (; data->assets.musics != NULL;
        data->assets.musics = next_music) {
        next_music = data->assets.musics->next;
        if (sfMusic_getStatus(data->assets.musics->music) != sfStopped)
            sfMusic_stop(data->assets.musics->music);
        sfMusic_destroy(data->assets.musics->music);
        free(data->assets.musics);
    }
}

void free_gui_and_environment_texture(data_t *data)
{
    gui_texture_t *next_gui = NULL;
    environment_texture_t *next_env = NULL;

    for (; data->assets.gui_textures != NULL;
        data->assets.gui_textures = next_gui) {
        next_gui = data->assets.gui_textures->next;
        sfTexture_destroy(data->assets.gui_textures->texture);
        free(data->assets.gui_textures);
    }
    for (; data->assets.environment_textures != NULL;
        data->assets.environment_textures = next_env) {
        next_env = data->assets.environment_textures->next;
        sfTexture_destroy(data->assets.environment_textures->texture);
        free(data->assets.environment_textures);
    }
}

void free_effects_and_entities(data_t *data)
{
    entities_texture_t *next_ent = NULL;
    effect_t *next_effect = NULL;

    for (; data->assets.effects != NULL;
        data->assets.effects = next_effect) {
        next_effect = data->assets.effects->next;
        if (sfMusic_getStatus(data->assets.effects->effect) != sfStopped)
            sfMusic_stop(data->assets.effects->effect);
        sfMusic_destroy(data->assets.effects->effect);
        free(data->assets.effects);
    }
    for (; data->assets.entities_textures != NULL;
        data->assets.entities_textures = next_ent) {
        next_ent = data->assets.entities_textures->next;
        sfTexture_destroy(data->assets.entities_textures->texture);
        free(data->assets.entities_textures);
    }
}

void free_enemy_types(data_t *data)
{
    enemy_type_t *next_type = NULL;

    for (; data->assets.enemy_types != NULL;
        data->assets.enemy_types = next_type) {
        next_type = data->assets.enemy_types->next;
        free(data->assets.enemy_types);
    }
}

void free_map_and_weapons(data_t *data)
{
    weapon_t *next_weapon = NULL;
    map_t *next_map = NULL;

    for (; data->assets.maps != NULL;
        data->assets.maps = next_map) {
        next_map = data->assets.maps->next;
        free(data->assets.maps);
    }
    for (; data->assets.weapons != NULL;
        data->assets.weapons = next_weapon) {
        next_weapon = data->assets.weapons->next;
        sfTexture_destroy(data->assets.weapons->texture);
        sfSprite_destroy(data->assets.weapons->sprite);
        if (sfMusic_getStatus(data->assets.weapons->music) != sfStopped)
            sfMusic_stop(data->assets.weapons->music);
        sfMusic_destroy(data->assets.weapons->music);
        free(data->assets.weapons);
    }
}
*/
