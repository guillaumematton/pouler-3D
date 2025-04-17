/*
** EPITECH PROJECT, 2025
** lib
** File description:
** free_array
*/

#include <stdio.h>
#include <stdlib.h>

void free_array(char **array)
{
    if (array == NULL)
        return;
    for (int i = 0; array[i] != NULL; i++)
        free(array[i]);
    free(array);
}
