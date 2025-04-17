/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** main
*/

#include "wolf3d.h"

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

int main(UNUSED int ac, char **av, char **env)
{
    data_t data;

    if (check_if_in_gui(env) == false)
        return 84;
    if (parse_args(&data, av))
        return 84;
    initialize_game(&data);
    main_loop(&data);
    //terminate_game(&data);
}
