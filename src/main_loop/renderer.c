/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** renderer
*/

#include "wolf3d.h"

void render_in_map(data_t *data, char **map)
{
    int screen_height = sfRenderWindow_getSize(data->window).y;
    int screen_width = sfRenderWindow_getSize(data->window).x;

    for (int x = 0; x < screen_width; x++) {
        float cameraX = 2 * x / (float)screen_width - 1;
        float rayDirX = data->player.dirX + data->player.planeX * cameraX;
        float rayDirY = data->player.dirY + data->player.planeY * cameraX;

        int mapX = (int)data->player.x;
        int mapY = (int)data->player.y;

        float sideDistX;
        float sideDistY;

        float deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
        float deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
        float perpWallDist;

        int stepX;
        int stepY;

        int hit = 0;
        int side;

        if (rayDirX < 0) {
            stepX = -1;
            sideDistX = (data->player.x - mapX) * deltaDistX;
        } else {
            stepX = 1;
            sideDistX = (mapX + 1.0 - data->player.x) * deltaDistX;
        }
        if (rayDirY < 0) {
            stepY = -1;
            sideDistY = (data->player.y - mapY) * deltaDistY;
        } else {
            stepY = 1;
            sideDistY = (mapY + 1.0 - data->player.y) * deltaDistY;
        }

        while (hit == 0) {
            if (sideDistX < sideDistY) {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            } else {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            if (map[mapX][mapY] > 0) hit = 1;
        }

        if (side == 0)
            perpWallDist = (mapX - data->player.x + (1 - stepX) / 2) / rayDirX;
        else
            perpWallDist = (mapY - data->player.y + (1 - stepY) / 2) / rayDirY;

        int lineHeight = (int)(screen_height / perpWallDist);

        int drawStart = -lineHeight / 2 + screen_height / 2;
        if (drawStart < 0) drawStart = 0;
        int drawEnd = lineHeight / 2 + screen_height / 2;
        if (drawEnd >= screen_height) drawEnd = screen_height - 1;

        float wallX;
        if (side == 0)
            wallX = data->player.y + perpWallDist * rayDirY;
        else
            wallX = data->player.x + perpWallDist * rayDirX;
        wallX -= floor(wallX);

        int texX = (int)(wallX * (float)TEX_SIZE);
        if (side == 0 && rayDirX > 0) texX = TEX_SIZE - texX - 1;
        if (side == 1 && rayDirY < 0) texX = TEX_SIZE - texX - 1;

        sfIntRect texRect = {texX, 0, 1, TEX_SIZE};
        sfSprite_setTextureRect(data->sprites.environment.walls, texRect);
        sfSprite_setScale(data->sprites.environment.walls, (sfVector2f){1.0f, (float)lineHeight / TEX_SIZE});
        sfSprite_setPosition(data->sprites.environment.walls, (sfVector2f){(float)x, (float)drawStart});
        sfRenderWindow_drawSprite(data->window, data->sprites.environment.walls, NULL);
    }
}
