/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** main
*/

#include "wolf3d.h"

//temp code vvv
int main_loop(data_t *data)
{
    sfEvent event;

    while (sfRenderWindow_isOpen(data->window)) {
        sfRenderWindow_clear(data->window, sfBlack);
        while (sfRenderWindow_pollEvent(data->window, &event) == 0)
            continue;
        if (event.type == sfEvtClosed)
            break;
    }
    return 0;
}
///temp code ^^^

static data_t initialize_data(void)
{
    data_t data = {{false, false, NULL},
    {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL}};

    return data;
}

int main(UNUSED int ac, char **av, char **env)
{
    data_t data = initialize_data();

    if (check_if_in_gui(env) == false)
        return 84;
    if (parse_args(&data, av))
        return 84;
    if (display_help(&data))
        return 0;
    initialize_game(&data);
    main_loop(&data);
    //terminate_game(&data);
}
