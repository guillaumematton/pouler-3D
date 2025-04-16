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

    #include "my.h"
    #include "assets.h"

typedef struct data {
    assets_t assets;
} data_t;

typedef struct player {
    float x;
    float y;
    float angle;
} player_t;

int main(int ac, char **av, char **env);
bool check_if_in_gui(char **env);
bool parse_args(data_t *data, char **av);
bool initialize_game(data_t *data);
bool load_data(data_t *data);

#endif
