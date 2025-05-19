/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** renderer
*/

#include "wolf3d.h"

static void fill_rays(data_t *data, ray_t *rays, int x, int screen_width)
{
    rays->rayDirX0 = data->player.dirX +
        data->player.planeX * (2 * x / (float)screen_width - 1);
    rays->rayDirY0 = data->player.dirY +
        data->player.planeY * (2 * x / (float)screen_width - 1);
}

static void fill_dists(data_t *data, ray_t *rays, dist_info_t *dists, int x)
{
    if (rays->rayDirX0 == 0)
        dists->deltaDistX = 1e30;
    else
        dists->deltaDistX = fabs(1 / rays->rayDirX0);
    if (rays->rayDirY0 == 0)
        dists->deltaDistY = 1e30;
    else
        dists->deltaDistY = fabs(1 / rays->rayDirY0);
    dists->mapX = (int)data->player.x;
    dists->mapY = (int)data->player.y;
}

static void find_step(data_t *data, ray_t *rays, dist_info_t *dists)
{
    if (rays->rayDirX0 < 0) {
        dists->stepX = -1;
        dists->sideDistX = (data->player.x -
            (int)data->player.x) * dists->deltaDistX;
    } else {
        dists->stepX = 1;
        dists->sideDistX = ((int)data->player.x
            + 1.0 - data->player.x) * dists->deltaDistX;
    }
    if (rays->rayDirY0 < 0) {
        dists->stepY = -1;
        dists->sideDistY = (data->player.y -
            (int)data->player.y) * dists->deltaDistY;
    } else {
        dists->stepY = 1;
        dists->sideDistY = ((int)data->player.y
            + 1.0 - data->player.y) * dists->deltaDistY;
    }
}

static void colisions(data_t *data, dist_info_t *dists, ray_t *rays)
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
        if (map[dists->mapX][dists->mapY] == 'A')
            dists->hit = 1;
    }
    if (dists->side == 0)
        dists->perpWallDist = ((int)data->player.x - data->player.x
            + (1 - dists->stepX) / 2) / rays->rayDirX0;
    else
        dists->perpWallDist = ((int)data->player.y - data->player.y
            + (1 - dists->stepY) / 2) / rays->rayDirY0;
}

static void get_draw_info(data_t *data, ray_t *rays,
    dist_info_t *dists, draw_info_t *draw)
{
    int screen_height = sfRenderWindow_getSize(data->window).y;
    int lineHeight = (int)(screen_height / dists->perpWallDist);
    int drawEnd = lineHeight / 2 + screen_height / 2;

    draw->draw_start = -lineHeight / 2 + screen_height / 2;
    if (draw->draw_start < 0)
        draw->draw_start = 0;
    if (drawEnd >= screen_height)
        drawEnd = screen_height - 1;
    if (dists->side == 0)
        draw->wallX = data->player.y + dists->perpWallDist * rays->rayDirY0;
    else
        draw->wallX = data->player.x + dists->perpWallDist * rays->rayDirX0;
    draw->wallX -= floor(draw->wallX);
    draw->texX = (int)(draw->wallX * (float)TILE_SIZE);
    if (dists->side == 0 && rays->rayDirX0 > 0)
        draw->texX = TILE_SIZE - draw->texX - 1;
    if (dists->side == 1 && rays->rayDirY0 < 0)
        draw->texX = TILE_SIZE - draw->texX - 1;
}

static void draw_walls(data_t *data, draw_info_t draw, int x)
{
    sfIntRect texRect = {draw.texX, 0, 1, TILE_SIZE};

    sfSprite_setTextureRect(data->sprites.environment.walls, texRect);
    sfSprite_setScale(data->sprites.environment.walls,
            (sfVector2f){1.0f, (float)draw.line_height / TILE_SIZE});
    sfSprite_setPosition(data->sprites.environment.walls,
            (sfVector2f){(float)x, (float)draw.draw_start});
    sfRenderWindow_drawSprite(data->window,
            data->sprites.environment.walls, NULL);
}

void render_in_map(data_t *data, char **map)
{
    int screen_height = sfRenderWindow_getSize(data->window).y;
    int screen_width = sfRenderWindow_getSize(data->window).x;
    dist_info_t dists = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    ray_t rays = {0, 0, 0, 0, 0};
    draw_info_t draw = {0, 0, 0, 0};

    for (int x = 0; x < screen_width; x++) {
        fill_rays(data, &rays, x, screen_width);
        fill_dists(data, &rays, &dists, x);
        find_step(data, &rays, &dists);
        colisions(data, &dists, &rays);
        get_draw_info(data, &rays, &dists, &draw);
        draw_walls(data, draw, x);
    }
    floor_and_ceiling_casting(data, screen_width, screen_height);
}
