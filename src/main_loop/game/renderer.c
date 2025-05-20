/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** renderer
*/

#include "wolf3d.h"

static ray_t create_ray_struct(data_t *data, int y)
{
    ray_t rays = {0, 0, 0, 0, 0};

    rays.rayDirX0 = data->player.dirX - data->player.planeX;
    rays.rayDirY0 = data->player.dirY - data->player.planeY;
    rays.rayDirX1 = data->player.dirX + data->player.planeX;
    rays.rayDirY1 = data->player.dirY + data->player.planeY;
    rays.rowDistance = (0.5f * SCREEN_HEIGHT) / (y - SCREEN_HEIGHT / 2);
    rays.stepX = rays.rowDistance * (rays.rayDirX1 - rays.rayDirX0) / SCREEN_WIDTH;
    rays.stepY = rays.rowDistance * (rays.rayDirY1 - rays.rayDirY0) / SCREEN_WIDTH;
    rays.floorX = data->player.x + rays.rowDistance * rays.rayDirX0;
    rays.floorY = data->player.y + rays.rowDistance * rays.rayDirY0;
    return rays;
}

static void create_verteces(data_t *data, ray_t rays, int x, int y)
{
    int cellX = (int)(rays.floorX);
    int cellY = (int)(rays.floorY);
    int tx = (int)(TEX_SIZE * (rays.floorX - cellX)) & (TEX_SIZE - 1);
    int ty = (int)(TEX_SIZE * (rays.floorY - cellY)) & (TEX_SIZE - 1);
    sfColor floorColor = sfImage_getPixel(data->sprites.environment.B, tx, ty);
    sfVertex floorPixel = {
        .position = (sfVector2f){x, y},
        .color = floorColor
    };
    sfVertex ceilPixel = {
        .position = (sfVector2f){x, SCREEN_HEIGHT - y},
        .color = floorColor
    };

    sfVertexArray_append(data->game_vertex, floorPixel);
    sfVertexArray_append(data->game_vertex, ceilPixel);
    sfRenderWindow_drawVertexArray(data->window, data->game_vertex, NULL);
    sfVertexArray_clear(data->game_vertex);
}

static void cast_floor_and_ceiling(data_t *data)
{
    ray_t rays = create_ray_struct(data, 0);

    for (int y = SCREEN_HEIGHT / 2 + 1; y < SCREEN_HEIGHT; y++) {        
        rays = create_ray_struct(data, y);
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            create_verteces(data, rays, x, y);
            rays.floorX += rays.stepX;
            rays.floorY += rays.stepY;
        }
    }
}

static dist_info_t create_dist_struct(data_t *data, int x, ray_t *rays)
{
    dist_info_t temp;
    float cameraX = 2.0f * x / (float)SCREEN_WIDTH - 1.0f;

    rays->rayDirX0 = data->player.dirX + data->player.planeX * cameraX;
    rays->rayDirY0 = data->player.dirY + data->player.planeY * cameraX;
    temp.mapX = (int)data->player.x;
    temp.mapY = (int)data->player.y;
    if (rays->rayDirX0 == 0)
        temp.deltaDistX = 1e30;
    else
        temp.deltaDistX = fabs(1 / rays->rayDirX0);
    if (rays->rayDirY0 == 0)
        temp.deltaDistY = 1e30;
    else
        temp.deltaDistY = fabs(1 / rays->rayDirY0);
    temp.hit = 0;
    return temp;
}

static void setup_raycasting(data_t *data, ray_t *rays, dist_info_t *dists)
{
    if (rays->rayDirX0 < 0) {
        dists->stepX = -1;
        dists->sideDistX = (data->player.x - dists->mapX) * dists->deltaDistX;
    } else {
        dists->stepX = 1;
        dists->sideDistX = (dists->mapX + 1.0 - data->player.x) * dists->deltaDistX;
    }
    if (rays->rayDirY0 < 0) {
        dists->stepY = -1;
        dists->sideDistY = (data->player.y - dists->mapY) * dists->deltaDistY;
    } else {
        dists->stepY = 1;
        dists->sideDistY = (dists->mapY + 1.0 - data->player.y) * dists->deltaDistY;
    }
}

static void ray_casting(data_t *data, dist_info_t *dists)
{
    while (dists->hit == 0) {
        if (dists->sideDistX < dists->sideDistY) {
            dists->sideDistX += dists->deltaDistX;
            dists->mapX += dists->stepX;
            dists->side = 0;
        } else {
            dists->sideDistY += dists->deltaDistY;
            dists->mapY += dists->stepY;
            dists->side = 1;
        }
        if (dists->mapX >= 0 && dists->mapY >= 0 && dists->mapX < data->assets.maps->x_size && dists->mapY < data->assets.maps->y_size) {
            if (data->assets.maps->walls[dists->mapX][dists->mapY] != ' ')
                dists->hit = 1;
        } else {
            break; // Avoid infinite loop
        }
    }
    if (dists->side == 0)
        dists->perpWallDist = (dists->sideDistX - dists->deltaDistX);
    else
        dists->perpWallDist = (dists->sideDistY - dists->deltaDistY);
}

static void wall_render(data_t *data)
{
    ray_t rays = {0, 0, 0, 0, 0};
    dist_info_t dists = create_dist_struct(data, 0, &rays);

    for (int x = 0; x < SCREEN_WIDTH; x++) {
        dists = create_dist_struct(data, x, &rays);
        setup_raycasting(data, &rays, &dists);
        ray_casting(data, &dists);
        int lineHeight = (int)(SCREEN_HEIGHT / dists.perpWallDist);
        int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
        if (drawStart < 0) drawStart = 0;
        int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
        if (drawEnd >= SCREEN_HEIGHT) drawEnd = SCREEN_HEIGHT - 1;
        float wallX;
        if (dists.side == 0)
            wallX = data->player.y + dists.perpWallDist * rays.rayDirY0;
        else
            wallX = data->player.x + dists.perpWallDist * rays.rayDirX0;
        wallX -= floor(wallX);

    int texX = (int)(wallX * (float)TEX_SIZE);
    if (dists.side == 0 && rays.rayDirX0 > 0) texX = TEX_SIZE - texX - 1;
    if (dists.side == 1 && rays.rayDirY0 < 0) texX = TEX_SIZE - texX - 1;

    // Draw each vertical pixel
    for (int y = drawStart; y < drawEnd; y++) {
        int d = y * 256 - SCREEN_HEIGHT * 128 + lineHeight * 128;
        int texY = ((d * TEX_SIZE) / lineHeight) / 256;

        // Clamp texY
        if (texY < 0) texY = 0;
        if (texY >= TEX_SIZE) texY = TEX_SIZE - 1;

        sfColor color = sfImage_getPixel(data->sprites.environment.G, texX, texY);

        // Darken the color if it's a side wall
        if (dists.side == 1) {
            color.r /= 2;
            color.g /= 2;
            color.b /= 2;
        }

        sfVertex pixel = {
            .position = (sfVector2f){x, y},
            .color = color
        };

        sfVertexArray_append(data->game_vertex, pixel);
        sfRenderWindow_drawVertexArray(data->window, data->game_vertex, NULL);
        sfVertexArray_destroy(data->game_vertex);
    }
    }
}

void render_in_map(data_t *data, char game_state)
{
    if (game_state == MENU)
        return;
    cast_floor_and_ceiling(data);
}
