/*
** EPITECH PROJECT, 2025
** lore_dump
** File description:
** dump the lore
*/

#include "wolf3d.h"

static void set_fullscreen_lore(data_t *data)
{
    set_position_scale(6.6, 100, 0, data->sprites.menu.lore_sprites.lore1);
    set_position_scale(6, 0, 0, data->sprites.menu.lore_sprites.lore2);
    set_position_scale(1.4, 100, 70, data->sprites.menu.lore_sprites.lore3);
    set_position_scale(1.2, 200, 0, data->sprites.menu.lore_sprites.lore4);
    set_position_scale(4, 0, 300, data->sprites.menu.lore_sprites.lore5);
    set_position_scale(1.6, 0, 70, data->sprites.menu.lore_sprites.lore6);
    set_position_scale(1.6, 0, 70, data->sprites.menu.lore_sprites.lore7);
    set_position_scale(1.6, 0, 70, data->sprites.menu.lore_sprites.lore8);
    set_position_scale(1.6, 0, 70, data->sprites.menu.lore_sprites.lore9);
}

static void set_sprite_positions_lore(data_t *data)
{
    if (!data->arguments.full_screen) {
        set_position_scale(3.3, 0, 0, data->sprites.menu.lore_sprites.lore1);
        set_position_scale(3, 0, 0, data->sprites.menu.lore_sprites.lore2);
        set_position_scale(0.7, 0, 70, data->sprites.menu.lore_sprites.lore3);
        set_position_scale(0.6, 100, 0, data->sprites.menu.lore_sprites.lore4);
        set_position_scale(2, 0, 180, data->sprites.menu.lore_sprites.lore5);
        set_position_scale(0.8, 0, 70, data->sprites.menu.lore_sprites.lore6);
        set_position_scale(0.8, 0, 70, data->sprites.menu.lore_sprites.lore7);
        set_position_scale(0.8, 0, 70, data->sprites.menu.lore_sprites.lore8);
        set_position_scale(0.8, 0, 70, data->sprites.menu.lore_sprites.lore9);
    } else
        set_fullscreen_lore(data);
    return;
}

void browse_sounds(data_t *data)
{
    sound_t *temp = data->assets.sounds;

    set_sprite_positions_lore(data);
    while (my_strcmp(temp->name, "lore.ogg") != 0 || !temp)
        temp = temp->next;
    if (!temp) {
        data->scene = MENU;
        return;
    }
    data->game_time = 0.0;
    sfSound_play(temp->sound);
}

static void display_lore_part1(data_t *data)
{
    if (data->game_time > 0.0 && data->game_time < 17.0)
        sfRenderWindow_drawSprite(data->window,
    data->sprites.menu.lore_sprites.lore1, NULL);
    if (data->game_time > 17.0 && data->game_time < 21.0)
        sfRenderWindow_drawSprite(data->window,
    data->sprites.menu.lore_sprites.lore2, NULL);
    if (data->game_time > 24.0 && data->game_time < 34.5)
        sfRenderWindow_drawSprite(data->window,
    data->sprites.menu.lore_sprites.lore3, NULL);
}

static void display_lore_part2(data_t *data)
{
    if (data->game_time > 34.5 && data->game_time < 50.0)
        sfRenderWindow_drawSprite(data->window,
    data->sprites.menu.lore_sprites.lore4, NULL);
    if (data->game_time > 50.0 && data->game_time < 85.0)
        sfRenderWindow_drawSprite(data->window,
    data->sprites.menu.lore_sprites.lore5, NULL);
}

static void display_lore_part3(data_t *data)
{
    if (data->game_time > 85.0 && data->game_time < 93.0)
        sfRenderWindow_drawSprite(data->window,
    data->sprites.menu.lore_sprites.lore6, NULL);
    if (data->game_time > 93.0 && data->game_time < 100.0)
        sfRenderWindow_drawSprite(data->window,
    data->sprites.menu.lore_sprites.lore7, NULL);
    if (data->game_time > 100.0 && data->game_time < 108.0)
        sfRenderWindow_drawSprite(data->window,
    data->sprites.menu.lore_sprites.lore8, NULL);
    if (data->game_time > 108.0 && data->game_time < 117.0)
        sfRenderWindow_drawSprite(data->window,
    data->sprites.menu.lore_sprites.lore9, NULL);
}

void display_lore_dump(data_t *data)
{
    display_lore_part1(data);
    display_lore_part2(data);
    display_lore_part3(data);
    if (data->game_time >= 117.0) {
        data->scene = MENU;
        if (data->arguments.debug)
            mini_printf("switching to menu scene.\n");
    }
}
