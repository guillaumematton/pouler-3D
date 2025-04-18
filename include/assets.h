/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** assets header
*/

#ifndef WOLF3D_ASSETS
    #define WOLF3D_ASSETS

    #include "wolf3d.h"

typedef struct music_s {
    sfMusic *music;
    struct music_s *next;
} music_t;

typedef struct effect {
    sfMusic *effect;
    struct effect *next;
} effect_t;

typedef struct enemy_type {
    struct enemy_type *next;
} enemy_type_t;

typedef struct map {
    u_int x_size;
    u_int y_size;
    struct map *next;
} map_t;

typedef struct weapon {
    sfTexture *texture;
    sfSprite *sprite;
    sfMusic *music;
    float damage;
    int ammo;
    int max_ammo;
    float firerate;
    bool explosive;
    bool melee;
    struct weapon *next;
} weapon_t;

typedef struct entities_texture {
    sfTexture *texture;
    struct entities_textures *next;
} entities_texture_t;

typedef struct environment_texture {
    sfTexture *texture;
    struct environment_texture *next;
} environment_texture_t;

typedef struct gui_texture {
    sfTexture *texture;
    struct gui_texture *next;
} gui_texture_t;

typedef struct assets {
    effect_t *effects;
    music_t *musics;
    enemy_type_t *enemy_types;
    map_t *maps;
    weapon_t *weapons;
    entities_texture_t *entities_textures;
    environment_texture_t *environment_textures;
    gui_texture_t *gui_textures;
} assets_t;

#endif
