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
        //TODO call help thingy
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
            //TODO call help thingy
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
    bool status = false;

    for (int i = 1; av[i] != NULL; i++) {
        if (status) {
            mini_printf("Try 'amazed -h' for more information.\n");
            return true;
        }
        if (av[i][0] == '-' && av[i][1] == '-') {
            status = parse_string_arg(data, av[i]);
            continue;
        }
        if (av[i][0] == '-') {
            status = parse_letter_arg(data, av[i]);
            continue;
        }
        mini_printf("wolf3d: invalid argument -- '%s'\n", av[i]);
        mini_printf("Try 'amazed -h' for more information.\n");
        return true;
    }
    return false;
}
