/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** sprite
*/

#ifndef SPRITE_H_
    #define SPRITE_H_
    #include "wolf3d.h"

typedef struct option_s {
    sfSprite *full_screen;
    sfSprite *volume_up;
    sfSprite *volume_down;
    sfSprite *volume;
    sfSprite *back;
    sfSprite *save;
} option_t;

typedef struct lore_s {
    sfSprite *lore1;
    sfSprite *lore2;
    sfSprite *lore3;
    sfSprite *lore4;
    sfSprite *lore5;
    sfSprite *lore6;
    sfSprite *lore7;
    sfSprite *lore8;
    sfSprite *lore9;
} lore_t;

typedef struct menu_s {
    sfSprite *title;
    sfSprite *background;
    sfSprite *p_background;
    sfSprite *o_background;
    sfSprite *new_game;
    sfSprite *continue_game;
    sfSprite *options;
    sfSprite *exit_game;
    sfSprite *lore;
    option_t options_sprites;
    lore_t lore_sprites;
} menu_t;

typedef struct menu_infos_s {
    sfFloatRect newgame_infos;
    sfFloatRect continuegame_infos;
    sfFloatRect options_infos;
    sfFloatRect lore_infos;
    sfFloatRect exit_infos;
    sfVector2i mouse_pos;
} menu_infos_t;

typedef struct pause_infos_s {
    sfFloatRect options_infos;
    sfFloatRect exit_infos;
    sfFloatRect save_infos;
    sfVector2i mouse_pos;
} pause_infos_t;

typedef struct options_infos_s {
    sfFloatRect fullscreen_infos;
    sfFloatRect volume_up_infos;
    sfFloatRect volume_down_infos;
    sfVector2i mouse_pos;
} options_infos_t;

typedef struct env_s {
    sfImage *image;
    char *name;
    struct env_s *next;
} env_t;

typedef struct enemy_sprite_s {
    sfSprite *enemy;
    struct enemy_sprite_s *next;
} enemy_sprite_t;

typedef struct sprite_s {
    menu_t menu;
    env_t *environment;
    enemy_sprite_t *enemies;
} sprite_t;

#endif /* !SPRITE_H_ */
