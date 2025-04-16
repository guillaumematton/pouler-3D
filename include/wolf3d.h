/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** header
*/

#ifndef WOLF3D
    #define WOLF3D

    #include "my.h"

typedef struct data {
} data_t;

typedef struct player {
    float x;
    float y;
    float angle;
} player_t;

typedef struct map {
    u_int x_size;
    u_int y_size;
} map_t;

int main(int ac, char **av, char **env);
bool check_if_in_gui(char **env);
bool parse_args(data_t *data, char **av);

#endif
