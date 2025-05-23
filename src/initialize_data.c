/*
** EPITECH PROJECT, 2025
** wolf3d.h
** File description:
** initialize_data
*/

#include "wolf3d.h"

data_t initialize_data(void)
{
    data_t data = {{false, false, false},
    {100, 0, 0, 0, 0, 0, 90}, NULL,
    {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
    {false, {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    {NULL, NULL, NULL, NULL, NULL, NULL, NULL}}, NULL, NULL},
    NULL, NULL, NULL, MENU, NULL, {0, 0}, {NULL, NULL, 0, 0, {0, 0}},
    {NULL, NULL, NULL, NULL}, false, {0}, 0, 0, NULL, 50.5};

    return data;
}
