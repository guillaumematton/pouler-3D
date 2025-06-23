/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** render_particules
*/

#include "wolf3d.h"


static void move_dust_particule(data_t *data, uint i)
{
    data->dust_particules[i].x_pos += data->dust_particules[i].x_vel
        * data->tick_duration * GAME_FPS;
    data->dust_particules[i].y_pos += data->dust_particules[i].y_vel
        * data->tick_duration * GAME_FPS;
}

static void respawn_dust_particule(data_t *data, uint i)
{
    if (data->dust_particules[i].x_pos <= 0 ||
        data->dust_particules[i].x_pos >= INTERNAL_WIDTH ||
        data->dust_particules[i].y_pos <= 0 ||
        data->dust_particules[i].y_pos >= INTERNAL_HEIGHT) {
        data->dust_particules[i].x_pos = rand() % INTERNAL_WIDTH;
        data->dust_particules[i].y_pos = rand() % INTERNAL_HEIGHT;
        data->dust_particules[i].x_vel = (rand() % 20 - 10) / 10.0;
        data->dust_particules[i].y_vel = (rand() % 20 - 10) / 10.0;
    }
}

static void render_dust_particule(data_t *data, uint i)
{
    sfColor color = sfColor_fromRGB(125, 125, 125);

    sfImage_setPixel(data->game_screen_image,
        data->dust_particules[i].x_pos,
        data->dust_particules[i].y_pos,
        color);
}

void render_particules(data_t *data)
{
    for (uint i = 0; i < DUST_PARTICULES_COUNT; i++) {
        move_dust_particule(data, i);
        respawn_dust_particule(data, i);
        render_dust_particule(data, i);
    }
}
