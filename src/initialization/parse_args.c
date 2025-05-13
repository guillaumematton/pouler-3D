/*
** EPITECH PROJECT, 2025
** parse_args
** File description:
** wolf3d
*/

#include "wolf3d.h"

//parses a "--text" argument
//returns true if error
static bool parse_string_arg(data_t *data, char *arg)
{
    if (my_strcmp(arg, "--help") == 0) {
        data->arguments.help = true;
        return false;
    }
    if (my_strcmp(arg, "--full_screen") == 0) {
        data->arguments.full_screen = true;
        return false;
    }
    if (my_strcmp(arg, "--debug") == 0) {
        data->arguments.debug = true;
        return false;
    }
    mini_printf("wolf3d: unrecognized option '%s'\n", arg);
    return true;
}

//parses a "-****" series of options
//returns true if error
static bool parse_letter_arg(data_t *data, char *arg)
{
    for (int i = 1; arg[i] != '\0'; i++) {
        switch (arg[i]) {
        case 'h':
            data->arguments.help = true;
            break;
        case 'f':
            data->arguments.full_screen = true;
            break;
        case 'd':
            data->arguments.debug = true;
            break;
        default:
            mini_printf("wolf3d: invalid option -- '%c'\n", arg[i]);
            return true;
        }
    }
    return false;
}

//parses the program arguments
//returns true if error
bool parse_args(data_t *data, char **av)
{
    bool err = false;

    for (int i = 1; av[i] != NULL && !err; i++) {
        if (av[i][0] == '-' && av[i][1] == '-') {
            err = parse_string_arg(data, av[i]);
            continue;
        }
        if (av[i][0] == '-') {
            err = parse_letter_arg(data, av[i]);
            continue;
        }
        mini_printf("wolf3d: invalid argument -- '%s'\n", av[i]);
        err = true;
    }
    if (err) {
        mini_printf("Try 'wolf3d -h' for more information.\n");
        return true;
    }
    return false;
}
