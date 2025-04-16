/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** initialize_game
*/

#include "wolf3d.h"

//does all the neccessary work to start the game (which you just lost)
//returns true if error
bool initialize_game(data_t *data)
{
    if (load_data(data))
        return true;
}
