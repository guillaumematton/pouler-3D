/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** player_movement
*/

#include "wolf3d.h"

static void handle_forward_input(Player_t *player, char **map, float moveSpeed)
{
    if (!sfKeyboard_isKeyPressed(sfKeyW))
        return;
    if (map[(int)(player->x + player->dirX * moveSpeed)]
        [(int)player->y] == 0) // 0 = block où on peut aller
        player->x += player->dirX * moveSpeed;
    if (map[(int)player->x]
        [(int)(player->y + player->dirY * moveSpeed)] == 0)
        player->y += player->dirY * moveSpeed;
}

static void handle_backward_input(Player_t *player, char **map,
    float moveSpeed)
{
    if (!sfKeyboard_isKeyPressed(sfKeyS))
        return;
    if (map[(int)(player->x - player->dirX * moveSpeed)]
        [(int)player->y] == 0)
        player->x -= player->dirX * moveSpeed;
    if (map[(int)player->x]
        [(int)(player->y - player->dirY * moveSpeed)] == 0)
        player->y -= player->dirY * moveSpeed;
}

static void handle_left_input(Player_t *player, char **map, float moveSpeed)
{
    float strafeX = -player->dirY;
    float strafeY = player->dirX;

    if (sfKeyboard_isKeyPressed(sfKeyQ))
        return;
    if (map[(int)(player->x + strafeX * moveSpeed)]
        [(int)player->y] == 0)
        player->x += strafeX * moveSpeed;
    if (map[(int)player->x]
        [(int)(player->y + strafeY * moveSpeed)] == 0)
        player->y += strafeY * moveSpeed;
}

static void handle_right_input(Player_t *player, char **map, float moveSpeed)
{
    float moveSpeed = 5.0f;
    float rotSpeed = 2.0f;
    float strafeX = player->dirY;
    float strafeY = -player->dirX;

    if (sfKeyboard_isKeyPressed(sfKeyD))
        return;
    if (map[(int)(player->x + strafeX * moveSpeed)]
        [(int)player->y] == 0)
        player->x += strafeX * moveSpeed;
    if (map[(int)player->x]
        [(int)(player->y + strafeY * moveSpeed)] == 0)
        player->y += strafeY * moveSpeed;
}

static void handle_camera_movement(Player_t *player,
    float rotSpeed, int deltaX)
{
    float oldDirX = player->dirX;
    float oldPlaneX = player->planeX;
    float rot = rotSpeed * deltaX;

    player->dirX = player->dirX * cos(-rot) - player->dirY * sin(-rot);
    player->dirY = oldDirX * sin(-rot) + player->dirY * cos(-rot);
    player->planeX = player->planeX * cos(-rot) - player->planeY * sin(-rot);
    player->planeY = oldPlaneX * sin(-rot) + player->planeY * cos(-rot);
}

void handle_movement(Player_t *player, char **map,
    sfClock *clock, data_t *data)
{
    sfTime elapsed = sfClock_getElapsedTime(clock);
    float delta_time = sfTime_asSeconds(elapsed);
    float moveSpeed = 5.0f * delta_time; // basic movement speed = 5.0f
    float rotSpeed = 0.1f * delta_time; // basic sensitivity = 0.1f
    sfVector2i mousePos = sfMouse_getPositionRenderWindow(data->window);
    sfVector2u screen = sfRenderWindow_getSize(data->window);
    int deltaX = mousePos.x - screen.x;

    sfMouse_setPositionRenderWindow((sfVector2i)
        {screen.x / 2, screen.y / 2}, data->window);
    handle_backward_input(player, map, moveSpeed);
    handle_forward_input(player, map, moveSpeed);
    handle_left_input(player, map, moveSpeed);
    handle_right_input(player, map, moveSpeed);
    sfClock_restart(clock);
}
