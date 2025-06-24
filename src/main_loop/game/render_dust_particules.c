/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** render_particules
*/

#include "wolf3d.h"

static void handle_player_movement_dust_particules_strafing(data_t *data)
{
    if (sfKeyboard_isKeyPressed(sfKeyD)) {
        for (uint i = 0; i < DUST_PARTICULES_COUNT; i++) {
            data->dust_particules[i].x_pos += -1
                * data->tick_duration * 1000;
        }
    }
    if (sfKeyboard_isKeyPressed(sfKeyQ)) {
        for (uint i = 0; i < DUST_PARTICULES_COUNT; i++) {
            data->dust_particules[i].x_pos += 1
                * data->tick_duration * 1000;
        }
    }
}

static void handle_player_movement_dust_particules_rotation(data_t *data)
{
    if (sfKeyboard_isKeyPressed(sfKeyE)) {
        for (uint i = 0; i < DUST_PARTICULES_COUNT; i++) {
            data->dust_particules[i].x_pos -=
            (180 / (0.2f * data->tick_duration)) / INTERNAL_WIDTH;
        }
    }
    if (sfKeyboard_isKeyPressed(sfKeyA)) {
        for (uint i = 0; i < DUST_PARTICULES_COUNT; i++) {
            data->dust_particules[i].x_pos +=
            (180 / (0.2f * data->tick_duration)) / INTERNAL_WIDTH;
        }
    }
}

static void check_screen_center_particule_colision(data_t *data, uint i)
{
    if (fabs((data->dust_particules[i].x_pos - (INTERNAL_WIDTH / 2)) *
        (0.2f * data->tick_duration) * 9)
        + fabs((data->dust_particules[i].y_pos - (INTERNAL_HEIGHT / 2)) *
        (0.2f * data->tick_duration) * 9) <= 3) {
        data->dust_particules[i].x_pos = rand() % INTERNAL_WIDTH;
        data->dust_particules[i].y_pos = rand() % INTERNAL_HEIGHT;
        data->dust_particules[i].x_vel = (rand() % 21 - 10) / 10.0;
        data->dust_particules[i].y_vel = (rand() % 21 - 10) / 10.0;
    }
}

static void handle_player_movement_dust_particules_forward_backward
(data_t *data)
{
    if (sfKeyboard_isKeyPressed(sfKeyZ))
        for (uint i = 0; i < DUST_PARTICULES_COUNT; i++) {
            data->dust_particules[i].x_pos +=
            (data->dust_particules[i].x_pos - (INTERNAL_WIDTH / 2)) *
            (0.2f * data->tick_duration) * 9;
            data->dust_particules[i].y_pos +=
            (data->dust_particules[i].y_pos - (INTERNAL_HEIGHT / 2)) *
            (0.2f * data->tick_duration) * 9;
        }
    if (sfKeyboard_isKeyPressed(sfKeyS))
        for (uint i = 0; i < DUST_PARTICULES_COUNT; i++) {
            check_screen_center_particule_colision(data, i);
            data->dust_particules[i].x_pos -=
            (data->dust_particules[i].x_pos - (INTERNAL_WIDTH / 2)) *
            (0.2f * data->tick_duration) * 9;
            data->dust_particules[i].y_pos -=
            (data->dust_particules[i].y_pos - (INTERNAL_HEIGHT / 2)) *
            (0.2f * data->tick_duration) * 9;
        }
}

static void handle_player_movement_dust_particules(data_t *data)
{
    handle_player_movement_dust_particules_strafing(data);
    handle_player_movement_dust_particules_rotation(data);
    handle_player_movement_dust_particules_forward_backward(data);
}

static void move_dust_particule(data_t *data)
{
    for (uint i = 0; i < DUST_PARTICULES_COUNT; i++) {
        data->dust_particules[i].x_pos += data->dust_particules[i].x_vel
        * data->tick_duration * GAME_FPS;
        data->dust_particules[i].y_pos += data->dust_particules[i].y_vel
        * data->tick_duration * GAME_FPS;
    }
}

static void respawn_dust_particule(data_t *data)
{
    for (uint i = 0; i < DUST_PARTICULES_COUNT; i++) {
        if (data->dust_particules[i].x_pos <= 0 ||
            data->dust_particules[i].x_pos >= INTERNAL_WIDTH ||
            data->dust_particules[i].y_pos <= 0 ||
            data->dust_particules[i].y_pos >= INTERNAL_HEIGHT) {
            data->dust_particules[i].x_pos = rand() % INTERNAL_WIDTH;
            data->dust_particules[i].y_pos = rand() % INTERNAL_HEIGHT;
            data->dust_particules[i].x_vel = (rand() % 21 - 10) / 10.0;
            data->dust_particules[i].y_vel = (rand() % 21 - 10) / 10.0;
        }
    }
}

static void render_dust_particule(data_t *data)
{
    sfColor color = sfColor_fromRGB(125, 125, 125);

    for (uint i = 0; i < DUST_PARTICULES_COUNT; i++) {
        sfImage_setPixel(data->game_screen_image,
        data->dust_particules[i].x_pos,
        data->dust_particules[i].y_pos,
        color);
    }
}

void render_dust_particules(data_t *data)
{
    handle_player_movement_dust_particules(data);
    move_dust_particule(data);
    respawn_dust_particule(data);
    render_dust_particule(data);
}
