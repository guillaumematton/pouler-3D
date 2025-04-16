/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** assets header
*/

#ifndef WOLF3D_ASSETS
    #define WOLF3D_ASSETS

    #include "wolf3d.h"

typedef struct assets {
    struct effect_t *effects;
    struct music_t *musics;
    struct enemy_type *enemy_types;
    struct map *maps;
    struct weapons *weapons;
    struct entities_texture *entities_textures;
    struct environment_texture *environment_textures;
    struct gui_texture *gui_textures;
} assets_t;

typedef struct effect {
    sfMusic *effect;
    struct effect *next;
} effect_t;

typedef struct music {
    sfMusic *music;
    struct music *next;
} music_t;

typedef struct enemy_type {
    struct enemy_type *next;
} enemy_type_t;

typedef struct map {
    u_int x_size;
    u_int y_size;
    struct map *next;
} map_t;

typedef struct weapon {
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

#endif
