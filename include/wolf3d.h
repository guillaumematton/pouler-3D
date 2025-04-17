/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** main header
*/

#ifndef WOLF3D
    #define WOLF3D

    #include <SFML/System.h>
    #include <SFML/Window.h>
    #include <SFML/Graphics.h>
    #include <SFML/Audio.h>
    #include <SFML/Window.h>
    #include <SFML/Window.h>
    #include <SFML/Graphics.h>
    #include <SFML/Window/Event.h>
    #include <SFML/Audio.h>
    #include <math.h>

    #include "my.h"
    #include "assets.h"
    #include "weapons.h"

typedef struct data {
    assets_t *assets;
} data_t;

#define TILE_SIZE 64

typedef struct Player_s {
    float health;
    float x;
    float y;
    float angle;
} Player_t;

void load_map(char *filename);
void init_player(Player_t *player);
int is_wall(int x, int y);
void print_help(void);
int main(int ac, char **av, char **env);
bool check_if_in_gui(char **env);
bool parse_args(data_t *data, char **av);
bool initialize_game(data_t *data);
bool load_data(data_t *data);

#endif
