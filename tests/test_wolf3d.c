/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** criterion tests for the wolf3d project
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "wolf3d.h"

extern char **environ;

void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(wolf3d, initialize_data, .init=redirect_all_std)
{
    data_t data = initialize_data();

    if (check_if_in_gui(environ) == false)
        return; 
    
    cr_assert(initialize_game(&data) == false);
    terminate_game(&data);
}
