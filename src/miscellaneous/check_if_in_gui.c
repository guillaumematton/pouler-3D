/*
** EPITECH PROJECT, 2025
** check_if_in_gui
** File description:
** wolf3d
*/

#include "wolf3d.h"

bool check_if_in_gui(char **env)
{
    for (int i = 0; env[i] != NULL; i++) {
        if (my_strlen(env[i]) > 8 &&
            my_strncmp(env[i], "DISPLAY=", 8) == 0) {
            return (true);
        }
    }
    my_putstr("wolf3d: error: no display\n");
    return (false);
}
