/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** main
*/

#include "wolf3d.h"

static data_t initialize_data(void)
{
    data_t data = {{false, false, false},
    {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
    NULL, NULL};

    return data;
}

int main(UNUSED int ac, char **av, char **env)
{
    data_t data = initialize_data();

    srand(time(NULL));
    if (check_if_in_gui(env) == false)
        return 84;
    if (parse_args(&data, av))
        return 84;
    if (display_help(&data))
        return 0;
    if (data.arguments.debug)
        my_putstr("debug mode enabled.\n");
    initialize_game(&data);
    run_loop(&data);
    terminate_game(&data);
}
