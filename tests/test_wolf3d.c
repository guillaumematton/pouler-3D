/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** criterion tests for the wolf3d project
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "wolf3d.h"

void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(wolf3d, initialize_data)
{
    data_t data = initialize_data();
    data.arguments.debug = true;
    
    cr_assert(initialize_game(&data) == false);
    terminate_game(&data);
}
