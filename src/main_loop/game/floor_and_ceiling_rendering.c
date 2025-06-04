/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** floor_and_ceiling_rendering
*/

#include "wolf3d.h"

static ray_t create_ray_struct(data_t *data, int y)
{
    ray_t rays = {0, 0, 0, 0, 0, 0, 0, 0, 0};

    rays.rayDirX0 = data->player.dirX - data->player.planeX;
    rays.rayDirY0 = data->player.dirY - data->player.planeY;
    rays.rayDirX1 = data->player.dirX + data->player.planeX;
    rays.rayDirY1 = data->player.dirY + data->player.planeY;
    rays.rowDistance = (0.5f * INTERNAL_HEIGHT)
        / (y - INTERNAL_HEIGHT / 2);
    rays.stepX = rays.rowDistance * (rays.rayDirX1 -
        rays.rayDirX0) / INTERNAL_WIDTH;
    rays.stepY = rays.rowDistance * (rays.rayDirY1 -
        rays.rayDirY0) / INTERNAL_WIDTH;
    rays.floorX = data->player.x + rays.rowDistance * rays.rayDirX0;
    rays.floorY = data->player.y + rays.rowDistance * rays.rayDirY0;
    return rays;
}

static sfColor get_color(sfImage *image, ray_t rays, int tx, int ty)
{
    sfColor Color = sfImage_getPixel(image,
        floor(tx / 1.5f), ty);

    Color.b /= (1 + rays.rowDistance / 2);
    Color.r /= (1 + rays.rowDistance / 2);
    Color.g /= (1 + rays.rowDistance / 2);
    return Color;
}

static void create_verteces(data_t *data, ray_t rays, int x, int y)
{
    int cellX = (int)(rays.floorX);
    int cellY = (int)(rays.floorY);
    int tx = (int)(TEX_SIZE * (rays.floorX - cellX)) & (TEX_SIZE - 1);
    int ty = (int)(TEX_SIZE * (rays.floorY - cellY)) & (TEX_SIZE - 1);
    sfColor floorColor = get_color(data->map.floor_image, rays, tx, ty);
    sfColor ceilColor = get_color(data->map.ceil_image, rays, tx, ty);

    sfImage_setPixel(data->game_screen_image, x, y, floorColor);
    sfImage_setPixel(data->game_screen_image, x,
        INTERNAL_HEIGHT - y, ceilColor);
}

void cast_floor_and_ceiling(data_t *data)
{
    ray_t rays = create_ray_struct(data, 0);

    for (unsigned int y = INTERNAL_HEIGHT / 2 + 1; y <
        INTERNAL_HEIGHT; y++) {
        rays = create_ray_struct(data, y);
        for (unsigned int x = 0; x < INTERNAL_WIDTH; x++) {
            create_verteces(data, rays, x, y);
            rays.floorX += rays.stepX;
            rays.floorY += rays.stepY;
        }
    }
}
