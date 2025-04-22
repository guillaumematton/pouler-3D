/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** assets header
*/

#ifndef WOLF3D_ASSETS
    #define WOLF3D_ASSETS

    #include "wolf3d.h"

//TODO: add char *name for all assets structs
typedef struct sound_s {
    char *name;
    sfSoundBuffer *sound;
    struct sound_s *next;
} sound_t;

typedef struct music_s {
    char *name;
    sfMusic *music;
    struct music_s *next;
} music_t;

typedef struct enemy_type_s {
    char *name;
    //TODO add all the neccessary data;
    //char *name
    //int *healh
    //(thoses are examples, i doubt we'll need enemy type names)
    //..............
    struct enemy_type_s *next;
} enemy_type_t;

typedef struct map_s {
    char *name;
    unsigned int x_size;
    unsigned int y_size;
    //TODO add all the neccessary data;
    //char **arr;
    //char *name;
    //..........
    struct map_s *next;
} map_t;

typedef struct weapon_s {
    char *name;
    sfTexture *texture;
    sfSprite *sprite;
    sfMusic *music;
    float damage;
    int ammo;
    int max_ammo;
    float firerate;
    bool explosive;
    bool melee;
    struct weapon_s *next;
} weapon_t;

typedef struct entity_texture_s {
    char *name;
    sfTexture *texture;
    struct entities_textures_s *next;
} entity_texture_t;

typedef struct environment_texture_s {
    char *name;
    sfTexture *texture;
    struct environment_texture_s *next;
} environment_texture_t;

typedef struct gui_texture_s {
    char *name;
    sfTexture *texture;
    struct gui_texture_s *next;
} gui_texture_t;

typedef struct assets_s {
    sound_t *sounds; //
    music_t *musics; //
    enemy_type_t *enemy_types; //
    map_t *maps;
    weapon_t *weapons;
    entity_texture_t *entity_textures; //
    environment_texture_t *environment_textures; //
    gui_texture_t *gui_textures; //
} assets_t;

#endif
