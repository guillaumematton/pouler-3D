/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** display_help
*/

#include "wolf3d.h"

static void print_help_message(void)
{
    my_putstr(COL_RESET COL_BOLD COL_UNDERLINE
        "LE JE DE LE POULER 3(D)'s manual\n\n"
        COL_RESET COL_BOLD);
}

static void print_pouler(void)
{
    my_putstr(COL_RESET COL_BOLD COL_IRED
        "           MM\n"
        COL_IWHITE
        "      |\\__/ `>\n"
        "       \\_  _/\n"
        "         ][\n"
        COL_RESET);
}

static void print_keybinds(void)
{
    my_putstr(COL_RESET COL_BOLD
        "BEYBINDS:\n\n"
        "LCtrl + K : close the game\n\n"
        "Z/S : move forward/backward\n"
        "Q/D : strafe left/right\n"
        "A/E : rotate left/right\n"
        "mouse : rotate left/right\n"
        "Left click : attack\n"
        "1/2/3/4/5 : weapon selection\n"
        "Lshift : sprint\n"
        "escape : pause (in game)\n"
        "enter : resume (in options and pause menu)\n\n"
        "(this layout was made for AZERTY keyboards)\n\n"
        COL_RESET);
}

static void print_infos(void)
{
    my_putstr(COL_RESET COL_BOLD
        "\nFor more information, read the README.md.\n"
        "If your computer catches fire, consider closing the game\n\n"
        COL_RESET);
}

bool display_help(data_t *data)
{
    if (data->arguments.help) {
        print_pouler();
        print_help_message();
        print_keybinds();
        print_pouler();
        print_infos();
        print_pouler();
        return true;
    } else {
        return false;
    }
}
