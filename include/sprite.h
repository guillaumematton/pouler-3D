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
    sfSprite *empty_box;
    sfSprite *full_box;
    sfSprite *back;
} option_t;

typedef struct menu_s {
    sfSprite *title;
    sfSprite *background;
    sfSprite *new_game;
    sfSprite *continue_game;
    sfSprite *options;
    sfSprite *exit_game;
    sfSprite *lore;
    option_t options_sprites;
} menu_t;

typedef struct menu_infos_s {
    sfFloatRect newgame_infos;
    sfFloatRect continuegame_infos;
    sfFloatRect options_infos;
    sfFloatRect lore_infos;
    sfFloatRect exit_infos;
    sfVector2i mouse_pos;
} menu_infos_t;

typedef struct env_s {
    sfImage *A;
    sfImage *B;
    sfImage *C;
    sfImage *D;
    sfImage *E;
    sfImage *F;
    sfImage *G;
    sfImage *H;
    sfImage *I;
} env_t;

typedef struct enemy_sprite_s {
    sfSprite *enemy;
    struct enemy_sprite_s *next;
} enemy_sprite_t;

typedef struct sprite_s {
    bool in_full_screen;
    menu_t menu;
    env_t environment;
    enemy_sprite_t *enemies;
} sprite_t;

#endif /* !SPRITE_H_ */
