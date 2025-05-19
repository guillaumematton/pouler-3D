/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** floor_casting
*/

#include "wolf3d.h"

void set_rays(ray_t *rays, data_t *data, int y, int screen_height)
{
    rays->rayDirX0 = data->player.dirX - data->player.planeX;
    rays->rayDirY0 = data->player.dirY - data->player.planeY;
    rays->rayDirX1 = data->player.dirX + data->player.planeX;
    rays->rayDirY1 = data->player.dirY + data->player.planeY;
    rays->rowDistance = (0.5f * screen_height) / (y - screen_height / 2);
}

sfIntRect get_texture_rect(data_t *data, float worldX, float worldY)
{
    int texX = 0;
    int texY = 0;
    environment_texture_t **env_txt = &data->assets.environment_textures;
    environment_texture_t *env = *env_txt;
    sfIntRect rect;
    sfVector2u texSize;

    for (; env != NULL && my_strcmp(env->name, "J") != 0;
        env = env->next);
    texSize = sfTexture_getSize(env->texture);
    texX = (int)(texSize.x * (worldX - (int)worldX)) & (texSize.x - 1);
    texY = (int)(texSize.y * (worldY - (int)worldY)) & (texSize.y - 1);
    rect = (sfIntRect){texX, texY, 1, 1};
    return rect;
}

void cast_floor(data_t *data, sfIntRect rect, int x, int y)
{
    sfSprite_setTextureRect(data->sprites.environment.floor, rect);
    sfSprite_setPosition(data->sprites.environment.floor,
        (sfVector2f){x, (float)y});
    sfSprite_setScale(data->sprites.environment.floor,
        (sfVector2f){1.0f, 1.0f}); // Vertical scale = 1 px
    sfRenderWindow_drawSprite(data->window,
        data->sprites.environment.floor, NULL);
}

void cast_ceiling(data_t *data, int x, int y, int screen_height)
{
    sfSprite_setPosition(data->sprites.environment.ceiling,
        (sfVector2f){x, (float)(screen_height - y)});
    sfSprite_setScale(data->sprites.environment.ceiling,
        (sfVector2f){1.0f, 1.0f});
    sfRenderWindow_drawSprite(data->window,
        data->sprites.environment.ceiling, NULL);
}

static float get_worldx(data_t *data, ray_t rays, int x, int screen_width)
{
    float worldX = data->player.x + rays.rowDistance *
        rays.rayDirX0 + x * rays.rowDistance *
        (rays.rayDirX1 - rays.rayDirX0) / screen_width;

    return worldX;
}

static float get_worldy(data_t *data, ray_t rays, int x, int screen_width)
{
    float worldY = data->player.y + rays.rowDistance *
        rays.rayDirY0 + x * rays.rowDistance *
        (rays.rayDirY1 - rays.rayDirY0) / screen_width;

    return worldY;
}

void floor_and_ceiling_casting(data_t *data,
    int screen_width, int screen_height)
{
    float worldX = 0;
    float worldY = 0;
    ray_t rays = {0, 0, 0, 0, 0};
    sfIntRect rect;

    for (int y = screen_height / 2 + 1; y < screen_height; y++) {
        set_rays(&rays, data, y, screen_height);
        for (int x = 0; x < screen_width; x++) {
            worldX = get_worldx(data, rays, x, screen_width);
            worldY = get_worldy(data, rays, x, screen_width);
            rect = get_texture_rect(data, worldX, worldY);
            cast_floor(data, rect, x, y);
            sfSprite_setTextureRect(data->sprites.environment.ceiling,
                rect);
            cast_ceiling(data, x, y, screen_height);
        }
    }
}
