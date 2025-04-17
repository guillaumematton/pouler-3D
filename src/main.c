/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** main
*/

#include "wolf3d.h"

int main_loop(sfRenderWindow *window, data_t *data)
{
    sfEvent event;

    while (sfRenderWindow_isOpen(window)) {
        sfRenderWindow_clear(window, sfGreen);
        while (sfRenderWindow_pollEvent(window, &event) == 0)
            continue;
        if (event.type == sfEvtClosed)
            break;
    }
    sfRenderWindow_close(window);
    return 0;
}

int set_window(data_t *data)
{
    sfVideoMode mode = {800, 600, 32};
    sfRenderWindow *window = sfRenderWindow_create(mode, "wolf3D",
        sfClose | sfResize, NULL);
    int err = 0;

    if (!window)
        return 84;
    sfRenderWindow_setVerticalSyncEnabled(window, sfTrue);
    err = main_loop(window, data);
    sfRenderWindow_destroy(window);
    return err;
}

int main(UNUSED int ac, char **av, char **env)
{
    data_t data;

    if (check_if_in_gui(env) == false)
        return 84;
    if (parse_args(&data, av))
        return 84;
    initialize_game(&data);
    set_window(&data);
    //terminate_game(&data);
}
