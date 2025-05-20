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
    sfTexture* wallTex = sfTexture_createFromFile("assets/core/textures/environment/G.png", NULL);
    sfImage* wallImg = sfTexture_copyToImage(wallTex);
    sfTexture* floorTex = sfTexture_createFromFile("assets/core/textures/environment/B.png", NULL);
    sfTexture* ceilTex = sfTexture_createFromFile("assets/core/textures/environment/B.png", NULL);
    sfImage* floorImg = sfTexture_copyToImage(floorTex);
    sfImage* ceilImg = sfTexture_copyToImage(ceilTex);

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
    // --- Existing raycasting calculations ---
    float cameraX = 2.0f * x / (float)SCREEN_WIDTH - 1.0f;
    float rayDirX = data->player.dirX + data->player.planeX * cameraX;
    float rayDirY = data->player.dirY + data->player.planeY * cameraX;

    int mapX = (int)data->player.x;
    int mapY = (int)data->player.y;

    float sideDistX;
    float sideDistY;

    float deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
    float deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
    float perpWallDist;

    int stepX, stepY;
    int hit = 0, side;

    // DDA setup
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

    // DDA loop
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
    if (mapX >= 0 && mapY >= 0 && mapX < data->assets.maps->x_size && mapY < data->assets.maps->y_size) {
        if (data->assets.maps->walls[mapX][mapY] != ' ')
            hit = 1;
    } else {
        break; // Avoid infinite loop
    }
}
    // Calculate distance to wall
    if (side == 0)
        perpWallDist = (sideDistX - deltaDistX);
    else
        perpWallDist = (sideDistY - deltaDistY);

    // Calculate height of line to draw
    int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);

    int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
    if (drawStart < 0) drawStart = 0;
    int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
    if (drawEnd >= SCREEN_HEIGHT) drawEnd = SCREEN_HEIGHT - 1;
    // Texture X coordinate
    float wallX;
    if (side == 0)
        wallX = data->player.y + perpWallDist * rayDirY;
    else
        wallX = data->player.x + perpWallDist * rayDirX;
    wallX -= floor(wallX);

    int texX = (int)(wallX * (float)TEX_SIZE);
    if (side == 0 && rayDirX > 0) texX = TEX_SIZE - texX - 1;
    if (side == 1 && rayDirY < 0) texX = TEX_SIZE - texX - 1;

    // Draw each vertical pixel
    for (int y = drawStart; y < drawEnd; y++) {
        int d = y * 256 - SCREEN_HEIGHT * 128 + lineHeight * 128;
        int texY = ((d * TEX_SIZE) / lineHeight) / 256;

        // Clamp texY
        if (texY < 0) texY = 0;
        if (texY >= TEX_SIZE) texY = TEX_SIZE - 1;

        sfColor color = sfImage_getPixel(wallImg, texX, texY);

        // Darken the color if it's a side wall
        if (side == 1) {
            color.r /= 2;
            color.g /= 2;
            color.b /= 2;
        }

        sfVertex pixel = {
            .position = (sfVector2f){x, y},
            .color = color
        };

        sfVertexArray* va = sfVertexArray_create();
        sfVertexArray_setPrimitiveType(va, sfPoints);
        sfVertexArray_append(va, pixel);
        sfRenderWindow_drawVertexArray(data->window, va, NULL);
        sfVertexArray_destroy(va);
    }
}
}
