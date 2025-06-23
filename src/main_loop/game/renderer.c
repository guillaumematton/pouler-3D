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
    float cameraX = 2.0f * x / (float)INTERNAL_WIDTH - 1.0f;

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

static bool hit_detection(dist_info_t *dists, map_t *map)
{
    if (dists->mapX < map->x_size &&
        dists->mapY < map->y_size) {
        if (map->map[dists->mapX][dists->mapY] == 'X')
            dists->hit = 1;
    } else {
        return true;
    }
    return false;
}

static void ray_casting(dist_info_t *dists,
    ray_t *rays, map_t *map)
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
        if (hit_detection(dists, map))
            break;
    }
    if (dists->side == 0)
        dists->perpWallDist = (dists->sideDistX - dists->deltaDistX);
    else
        dists->perpWallDist = (dists->sideDistY - dists->deltaDistY);
}

static void draw_pixel(data_t *data, dist_info_t *dists, int x, int y)
{
    sfColor color = {0, 0, 0, 0};
    float color_diming = 1 + dists->perpWallDist / 10;

    if (dists->texY < 0)
        dists->texY = 0;
    if (dists->texY >= TEX_SIZE)
        dists->texY = TEX_SIZE - 1;
    color = sfImage_getPixel(data->map.walls_image,
        dists->texX, dists->texY);
    color.r /= color_diming;
    color.g /= color_diming;
    color.b /= color_diming;
    sfImage_setPixel(data->game_screen_image, x, y, color);
}

static void finish_filling_distances(dist_info_t *dists,
    ray_t rays, draw_info_t draw)
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
    draw->line_height = (int)(INTERNAL_HEIGHT / dists.perpWallDist);
    draw->draw_start = -draw->line_height / 2 + INTERNAL_HEIGHT / 2;
    if (draw->draw_start < 0)
        draw->draw_start = 0;
    draw->draw_end = draw->line_height / 2 + INTERNAL_HEIGHT / 2;
    if (draw->draw_end >= INTERNAL_HEIGHT)
        draw->draw_end = INTERNAL_HEIGHT - 1;
    if (dists.side == 0)
        draw->wallX = data->player.y + dists.perpWallDist * rays.rayDirY0;
    else
        draw->wallX = data->player.x + dists.perpWallDist * rays.rayDirX0;
    draw->wallX -= floor(draw->wallX);
    return draw->wallX;
}

static void wall_render(data_t *data, map_t *map)
{
    ray_t rays = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    dist_info_t dists = create_dist_struct(data, 0, &rays);
    draw_info_t draw = {0, 0, 0, 0, 0};
    int d = 0;

    for (unsigned int x = 0; x < INTERNAL_WIDTH;
        x++) {
        dists = create_dist_struct(data, x, &rays);
        setup_raycasting(data, &rays, &dists);
        ray_casting(&dists, &rays, map);
        draw.wallX = fill_draw(data, rays, dists, &draw);
        finish_filling_distances(&dists, rays, draw);
        for (unsigned int y = draw.draw_start; y < draw.draw_end;
            y++) {
            d = y * 256 - INTERNAL_HEIGHT * 128 + draw.line_height * 128;
            dists.texY = (((d * TEX_SIZE) /
            draw.line_height) / 256) % TEX_SIZE;
            draw_pixel(data, &dists, x, y);
        }
    }
}

void render_game(data_t *data, map_t *map)
{
    cast_floor_and_ceiling(data);
    wall_render(data, map);
    render_dust_particules(data);
    sfTexture_updateFromImage(data->game_screen_text,
        data->game_screen_image, 0, 0);
    sfSprite_setTexture(data->game_screen, data->game_screen_text, sfTrue);
    if (data->arguments.full_screen)
        sfSprite_setScale(data->game_screen,
            (sfVector2f){(float)data->screen_size.x / INTERNAL_WIDTH,
            (float)data->screen_size.y / INTERNAL_HEIGHT});
    sfRenderWindow_drawSprite(data->window, data->game_screen, NULL);
}
