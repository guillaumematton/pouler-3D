/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** renderer
*/

#include "wolf3d.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define TEX_SIZE 48

void render_in_map(data_t *data, char game_state)
{
    sfTexture* wallTex = sfTexture_createFromFile("assets/core/textures/environment/J", NULL);
    sfSprite* wallSlice = sfSprite_create();
    sfTexture* floorTex = sfTexture_createFromFile("assets/core/textures/environment/B", NULL);
    sfTexture* ceilTex = sfTexture_createFromFile("assets/core/textures/environment/B", NULL);
    sfImage* floorImg = sfTexture_copyToImage(floorTex);
    sfImage* ceilImg = sfTexture_copyToImage(ceilTex);
    sfSprite_setTexture(wallSlice, wallTex, sfTrue);

    if (game_state == MENU)
        return;
    for (int y = SCREEN_HEIGHT / 2 + 1; y < SCREEN_HEIGHT; y++) {
        float rayDirX0 = data->player.dirX - data->player.planeX;
        float rayDirY0 = data->player.dirY - data->player.planeY;
        float rayDirX1 = data->player.dirX + data->player.planeX;
        float rayDirY1 = data->player.dirY + data->player.planeY;

        int p = y - SCREEN_HEIGHT / 2;
        float posZ = 0.5f * SCREEN_HEIGHT;

        float rowDist = posZ / p;

        float stepX = rowDist * (rayDirX1 - rayDirX0) / SCREEN_WIDTH;
        float stepY = rowDist * (rayDirY1 - rayDirY0) / SCREEN_WIDTH;

        float floorX = data->player.x + rowDist * rayDirX0;
        float floorY = data->player.y + rowDist * rayDirY0;

        for (int x = 0; x < SCREEN_WIDTH; ++x) {
            int cellX = (int)(floorX);
            int cellY = (int)(floorY);

            int tx = (int)(TEX_SIZE * (floorX - cellX)) & (TEX_SIZE - 1);
            int ty = (int)(TEX_SIZE * (floorY - cellY)) & (TEX_SIZE - 1);

            sfColor floorColor = sfImage_getPixel(floorImg, tx, ty);
            sfColor ceilColor = sfImage_getPixel(ceilImg, tx, ty);

            sfVertex floorPixel = {
                .position = (sfVector2f){x, y},
                .color = floorColor
            };
            sfVertex ceilPixel = {
                .position = (sfVector2f){x, SCREEN_HEIGHT - y},
                .color = ceilColor
            };

            sfVertexArray* va = sfVertexArray_create();
            sfVertexArray_setPrimitiveType(va, sfPoints);
            sfVertexArray_append(va, floorPixel);
            sfVertexArray_append(va, ceilPixel);
            sfRenderWindow_drawVertexArray(data->window, va, NULL);
            sfVertexArray_destroy(va);
        
            floorX += stepX;
            floorY += stepY;
    }
}
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
