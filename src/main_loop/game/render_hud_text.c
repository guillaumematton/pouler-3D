/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** render_hud_text
*/

#include "wolf3d.h"

void render_hud_text(data_t *data)
{
    char buffer[34] = "\0";

    if (data->current_weapon.weapon->max_ammo > 0) {
        sprintf(buffer, "health: %i\nammo : %i/%i",
            (int) data->player.health,
            data->current_weapon.weapon->ammo,
            data->current_weapon.weapon->max_ammo);
    } else {
        sprintf(buffer, "health: %i\ninfinite ammo",
            (int) data->player.health);
    }
    sfText_setString(data->hud_text, buffer);
    sfRenderWindow_drawText(data->window, data->hud_text, NULL);
}
