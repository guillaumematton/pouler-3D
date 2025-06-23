/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** run_game_scene
*/

#include "wolf3d.h"

static bool find_image(data_t *data, char *name, sfImage **adress)
{
    env_t *env = data->sprites.environment;

    for (; env != NULL && my_strncmp(env->name, name, my_strlen(name))
        != 0; env = env->next);
    if (env == NULL) {
        data->exit = true;
        return true;
    }
    *adress = env->image;
    return false;
}

static void set_player(data_t *data, int x, int y)
{
    data->player.health = 100;
    data->player.x = x;
    data->player.y = y;
    data->player.dirX = 1;
    data->player.dirY = 0;
    data->player.planeX = 0;
    data->player.planeY = 0.9;
}

static bool set_new_player_pos(data_t *data, int y)
{
    for (int x = 0; data->map.current_map->map[y][x] != '\0'; x++)
        if (data->map.current_map->map[x][y] == 'S') {
            set_player(data, x, y);
            return true;
        }
    return false;
}

bool set_new_map(data_t *data, char *name)
{
    map_t *map_list = data->assets.maps;

    for (; map_list != NULL && my_strncmp(map_list->name,
        name, my_strlen(name))
        != 0; map_list = map_list->next);
    if (map_list == NULL)
        map_list = data->assets.maps;
    data->map.current_map = map_list;
    if (find_image(data, map_list->ceiling_texture_name,
        &data->map.ceil_image))
        return true;
    if (find_image(data, map_list->floor_texture_name, &data->map.floor_image))
        return true;
    if (find_image(data, map_list->wall_texture_name, &data->map.walls_image))
        return true;
    for (int y = 0; data->map.current_map->map[y] != NULL; y++)
        if (set_new_player_pos(data, y))
            return false;
    set_player(data, 3, 3);
    return false;
}

static bool parsing_game_map(data_t *data)
{
    if (data->map.current_map == NULL) {
        if (set_new_map(data, "start.lvl"))
            return true;
        return false;
    }
    if (data->map.current_map->map[(int)floor(data->player.x)]
        [(int)floor(data->player.y)] == 'T') {
        data->score += 1000;
        if (set_new_map(data, data->map.current_map->next_map_name))
            return true;
    }
    if (data->map.current_map->map[(int)floor(data->player.y)]
        [(int)floor(data->player.x)] == 'W') {
        if (data->arguments.debug)
            printf("switching to win screen scene.\n");
        data->scene = WIN_SCREEN;
        return true;
    }
    return false;
}

void run_game_scene(data_t *data)
{
    if (parsing_game_map(data))
        return;
    if (sfKeyboard_isKeyPressed(sfKeyEscape)) {
        data->scene = PAUSE;
        if (data->arguments.debug)
            printf("switching to pause scene.\n");
        return;
    }
    handle_firearms(data);
    handle_movement(data->map.current_map->map, data);
    render_game(data, data->map.current_map);
    sfRenderWindow_drawSprite(data->window,
    data->current_weapon.current_sprite, NULL);
    render_hud_text(data);
    draw_minimap(data);
}
