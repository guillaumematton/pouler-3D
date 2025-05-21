/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** player_movement
*/

#include "wolf3d.h"

static void handle_forward_input(data_t *data, char **map, float moveSpeed)
{
    if (!sfKeyboard_isKeyPressed(sfKeyZ))
        return;
    if (map[(int)(data->player.x + data->player.dirX * moveSpeed)]
        [(int)data->player.y] == ' ') // 0 = block où on peut aller
        data->player.x += data->player.dirX * moveSpeed;
    if (map[(int)data->player.x]
        [(int)(data->player.y + data->player.dirY * moveSpeed)] == ' ')
        data->player.y += data->player.dirY * moveSpeed;
}

static void handle_backward_input(data_t *data, char **map,
    float moveSpeed)
{
    if (!sfKeyboard_isKeyPressed(sfKeyS))
        return;
    if (map[(int)(data->player.x - data->player.dirX * moveSpeed)]
        [(int)data->player.y] == ' ')
        data->player.x -= data->player.dirX * moveSpeed;
    if (map[(int)data->player.x]
        [(int)(data->player.y - data->player.dirY * moveSpeed)] == ' ')
        data->player.y -= data->player.dirY * moveSpeed;
}

static void handle_right_input(data_t *data, char **map, float moveSpeed)
{
    float strafeX = -data->player.dirY;
    float strafeY = data->player.dirX;

    if (!sfKeyboard_isKeyPressed(sfKeyD))
        return;
    if (map[(int)(data->player.x + strafeX * moveSpeed)]
        [(int)data->player.y] == ' ')
        data->player.x += strafeX * moveSpeed;
    if (map[(int)data->player.x]
        [(int)(data->player.y + strafeY * moveSpeed)] == ' ')
        data->player.y += strafeY * moveSpeed;
}

static void handle_left_input(data_t *data, char **map, float moveSpeed)
{
    float rotSpeed = 2.0f;
    float strafeX = data->player.dirY;
    float strafeY = -data->player.dirX;

    if (!sfKeyboard_isKeyPressed(sfKeyQ))
        return;
    if (map[(int)(data->player.x + strafeX * moveSpeed)]
        [(int)data->player.y] == ' ')
        data->player.x += strafeX * moveSpeed;
    if (map[(int)data->player.x]
        [(int)(data->player.y + strafeY * moveSpeed)] == ' ')
        data->player.y += strafeY * moveSpeed;
}

static void handle_camera_movement(data_t *data,
    float rotSpeed, int deltaX)
{
    float oldDirX = data->player.dirX;
    float oldPlaneX = data->player.planeX;
    float rot = rotSpeed * deltaX;

    if (sfKeyboard_isKeyPressed(sfKeyA))
        deltaX += 20;
    if (sfKeyboard_isKeyPressed(sfKeyE))
        deltaX -= 20;
    rot = rotSpeed * deltaX;
    data->player.dirX = data->player.dirX * cos(-rot)
        - data->player.dirY * sin(-rot);
    data->player.dirY = oldDirX * sin(-rot) +
        data->player.dirY * cos(-rot);
    data->player.planeX = data->player.planeX *
        cos(-rot) - data->player.planeY * sin(-rot);
    data->player.planeY = oldPlaneX * sin(-rot) +
        data->player.planeY * cos(-rot);
}

void handle_movement(char **map,
    data_t *data, char game_state)
{
    sfTime elapsed = sfClock_getElapsedTime(data->clock);
    float delta_time = sfTime_asSeconds(elapsed);
    float moveSpeed = 2.0f * delta_time; // basic movement speed = 2.0f
    float rotSpeed = 0.1f * delta_time; // basic sensitivity = 0.1f
    sfVector2i mousePos = sfMouse_getPositionRenderWindow(data->window);
    sfVector2u screen = sfRenderWindow_getSize(data->window);
    int deltaX = screen.x / 2 - mousePos.x;

    sfClock_restart(data->clock);
    if (game_state != GAME)
        return;
    sfMouse_setPositionRenderWindow((sfVector2i)
        {screen.x / 2, screen.y / 2}, data->window);
    handle_backward_input(data, map, moveSpeed);
    handle_forward_input(data, map, moveSpeed);
    handle_left_input(data, map, moveSpeed);
    handle_right_input(data, map, moveSpeed);
    handle_camera_movement(data, rotSpeed, deltaX);
}
