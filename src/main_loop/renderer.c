/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** renderer
*/

#include "wolf3d.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define TEX_SIZE 64

void render_in_map(data_t *data, char game_state)
{
    sfTexture* wallTex = sfTexture_createFromFile("assets/core/textures/environment/J", NULL);
    sfSprite* wallSlice = sfSprite_create();
    sfSprite_setTexture(wallSlice, wallTex, sfTrue);
    data->player.x = 2;
    data->player.y = 1;  // Player position
    data->player.dirX = 1;
    data->player.dirY = 0;   // Initial direction
    data->player.planeX = 0;
    data->player.planeY = 0.66; // Camera plane

    if (game_state == MENU)
        return;
    for (int x = 0; x < SCREEN_WIDTH; x++) {
            float cameraX = 2 * x / (float)SCREEN_WIDTH - 1;
            float rayDirX = data->player.dirX + data->player.planeX * cameraX;
            float rayDirY = data->player.dirY + data->player.planeY * cameraX;

            int mapX = (int)data->player.x;
            int mapY = (int)data->player.y;

            float sideDistX, sideDistY;
            float deltaDistX = rayDirX == 0 ? 1e30 : fabs(1 / rayDirX);
            float deltaDistY = rayDirY == 0 ? 1e30 : fabs(1 / rayDirY);
            float perpWallDist;

            int stepX, stepY, hit = 0, side;

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
                if (data->assets.maps->walls[mapX][mapY] == 'A') hit = 1;
            }

            if (side == 0)
                perpWallDist = (mapX - data->player.x + (1 - stepX) / 2) / rayDirX;
            else
                perpWallDist = (mapY - data->player.y + (1 - stepY) / 2) / rayDirY;

            int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);
            int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
            int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;

            float wallX;
            if (side == 0)
                wallX = data->player.y + perpWallDist * rayDirY;
            else
                wallX = data->player.x + perpWallDist * rayDirX;
            wallX -= floor(wallX);

            int texX = (int)(wallX * (float)TEX_SIZE);
            if ((side == 0 && rayDirX > 0) || (side == 1 && rayDirY < 0))
                texX = TEX_SIZE - texX - 1;

            sfSprite_setTextureRect(wallSlice, (sfIntRect){texX, 0, 1, TEX_SIZE});
            sfSprite_setScale(wallSlice, (sfVector2f){1.0f, (float)lineHeight / TEX_SIZE});
            sfSprite_setPosition(wallSlice, (sfVector2f){x, (float)drawStart});
            sfRenderWindow_drawSprite(data->window, wallSlice, NULL);
        }
}
