/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** renderer
*/

#include "wolf3d.h"

static dist_info_t create_dist_struct(data_t *data, int x, ray_t *rays)
{
    dist_info_t temp;
    float cameraX = 2.0f * x / (float)data->screen_size.x - 1.0f;

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
        rays->stepX = -1;
        dists->sideDistX = (data->player.x - dists->mapX) * dists->deltaDistX;
    } else {
        rays->stepX = 1;
        dists->sideDistX = (dists->mapX + 1.0 -
            data->player.x) * dists->deltaDistX;
    }
    if (rays->rayDirY0 < 0) {
        rays->stepY = -1;
        dists->sideDistY = (data->player.y - dists->mapY) * dists->deltaDistY;
    } else {
        rays->stepY = 1;
        dists->sideDistY = (dists->mapY + 1.0 -
            data->player.y) * dists->deltaDistY;
    }
}

static bool hit_detection(data_t *data, dist_info_t *dists)
{
    if (dists->mapX >= 0 && dists->mapY >= 0 && dists->mapX <
        data->assets.maps->x_size &&
        dists->mapY < data->assets.maps->y_size) {
        if (data->assets.maps->walls[dists->mapX][dists->mapY] != ' ')
            dists->hit = 1;
    } else {
        return true;
    }
    return false;
}

static void ray_casting(data_t *data, dist_info_t *dists, ray_t *rays)
{
    while (dists->hit == 0) {
        if (dists->sideDistX < dists->sideDistY) {
            dists->sideDistX += dists->deltaDistX;
            dists->mapX += rays->stepX;
            dists->side = 0;
        } else {
            dists->sideDistY += dists->deltaDistY;
            dists->mapY += rays->stepY;
            dists->side = 1;
        }
        if (hit_detection(data, dists))
            break;
    }
    if (dists->side == 0)
        dists->perpWallDist = (dists->sideDistX - dists->deltaDistX);
    else
        dists->perpWallDist = (dists->sideDistY - dists->deltaDistY);
}

static void draw_pixel(data_t *data, dist_info_t *dists, int x, int y)
{
    sfColor color;
    sfVertex pixel = {0, 0};

    if (dists->texY < 0)
        dists->texY = 0;
    if (dists->texY >= TEX_SIZE)
        dists->texY = TEX_SIZE - 1;
    color = sfImage_getPixel(data->sprites.environment.G,
        dists->texX, dists->texY);
    if (dists->side == 1) {
        color.r /= 2;
        color.g /= 2;
        color.b /= 2;
    }
    pixel.position = (sfVector2f){x, y};
    pixel.color = color;
    sfVertexArray_append(data->game_vertex, pixel);
}

static void finish_filling_distances(dist_info_t *dists, ray_t rays, draw_info_t draw)
{
    dists->texX = (int)((float)draw.wallX * (float)TEX_SIZE);
    if (dists->side == 0 && rays.rayDirX0 > 0)
        dists->texX = TEX_SIZE - dists->texX - 1;
    if (dists->side == 1 && rays.rayDirY0 < 0)
        dists->texX = TEX_SIZE - dists->texX - 1;
    if (dists->texX < 0)
        dists->texX = 0;
    if (dists->texX >= TEX_SIZE)
        dists->texX = TEX_SIZE - 1;
}

static float fill_draw(data_t *data, ray_t rays,
    dist_info_t dists, draw_info_t *draw)
{
    draw->line_height = (int)(data->screen_size.y / dists.perpWallDist);
    draw->draw_start = -draw->line_height / 2 + data->screen_size.y / 2;
    if (draw->draw_start < 0)
        draw->draw_start = 0;
    draw->draw_end = draw->line_height / 2 + data->screen_size.y / 2;
    if (draw->draw_end >= data->screen_size.y)
        draw->draw_end = data->screen_size.y - 1;
    if (dists.side == 0)
        draw->wallX = data->player.y + dists.perpWallDist * rays.rayDirY0;
    else
        draw->wallX = data->player.x + dists.perpWallDist * rays.rayDirX0;
    draw->wallX -= floor(draw->wallX);
    return draw->wallX;
}

static void wall_render(data_t *data)
{
    ray_t rays = {0, 0, 0, 0, 0};
    dist_info_t dists = create_dist_struct(data, 0, &rays);
    draw_info_t draw = {0, 0, 0, 0};
    int d = 0;

    for (int x = 0; x < data->screen_size.x; x++) {
        dists = create_dist_struct(data, x, &rays);
        setup_raycasting(data, &rays, &dists);
        ray_casting(data, &dists, &rays);
        draw.wallX = fill_draw(data, rays, dists, &draw);
        finish_filling_distances(&dists, rays, draw);
        for (int y = draw.draw_start; y < draw.draw_end; y++) {
            d = y * 256 - data->screen_size.y * 128 + draw.line_height * 128;
            dists.texY = (((d * TEX_SIZE) /
            draw.line_height) / 256) % TEX_SIZE;
            draw_pixel(data, &dists, x, y);
        }
    }
}

void render_map(data_t *data)
{
    sfVector2u window_size = sfRenderWindow_getSize(data->window);

    cast_floor_and_ceiling(data);
    wall_render(data);
    sfRenderWindow_drawVertexArray(data->window, data->game_vertex, NULL);
    sfVertexArray_clear(data->game_vertex);
}
