/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** draw_minimap
*/

#include "wolf3d.h"

void draw_tile(data_t *data, int x, int y)
{
    if (data->map.current_map->map[x][y] == 'X')
        sfRectangleShape_setFillColor(data->tile,
        sfColor_fromRGB(200, 200, 200));
    if (data->map.current_map->map[x][y] == 'S')
        sfRectangleShape_setFillColor(data->tile, sfColor_fromRGB(0, 200, 0));
    if (data->map.current_map->map[x][y] == ' ')
        sfRectangleShape_setFillColor(data->tile, sfColor_fromRGB(10, 10, 10));
    if (data->map.current_map->map[x][y] == 'T')
        sfRectangleShape_setFillColor(data->tile, sfColor_fromRGB(200, 0, 0));
    if ((int)floor(data->player.x) == x && (int)floor(data->player.y) == y)
        sfRectangleShape_setFillColor(data->tile, sfColor_fromRGB(0, 0, 200));
    if (data->map.current_map->map[x][y] == 'W')
        sfRectangleShape_setFillColor(data->tile,
        sfColor_fromRGB(200, 200, 0));
    sfRenderWindow_drawRectangleShape(data->window, data->tile, NULL);
}

void draw_minimap(data_t *data)
{
    sfVector2f pos = {0, 0};
    sfVector2f size = {5, 5};

    for (unsigned int y = 0; y < data->map.current_map->y_size; y++) {
        for (unsigned int x = 0; x < data->map.current_map->x_size; x++) {
            pos.x = data->screen_size.x -
                data->map.current_map->x_size * 6 - 5 + x * 6;
            pos.y = 5 + y * 6;
            sfRectangleShape_setPosition(data->tile, pos);
            sfRectangleShape_setSize(data->tile, size);
            draw_tile(data, x, y);
        }
    }
}
