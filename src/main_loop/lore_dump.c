/*
** EPITECH PROJECT, 2025
** lore_dump
** File description:
** dump the lore
*/

#include "wolf3d.h"

static void set_fullscreen_pause(data_t *data)
{
    sfVector2f scale = {5, 6};
    sfVector2f position = {0, 0};

    sfSprite_setPosition(data->sprites.menu.p_background, position);
    sfSprite_setScale(data->sprites.menu.p_background, scale);
    set_position_scale(1, 730, 100, data->sprites.menu.options);
    set_position_scale(1, 760, 900, data->sprites.menu.exit_game);
}

static void set_sprite_positions_lore(data_t *data)
{
    if (!data->arguments.full_screen) {
        set_position_scale(3, 0, 0, data->sprites.menu.lore_sprites.lore1);
        set_position_scale(3, 0, 0, data->sprites.menu.lore_sprites.lore2);
        set_position_scale(3, 0, 0, data->sprites.menu.lore_sprites.lore3);
        set_position_scale(3, 0, 0, data->sprites.menu.lore_sprites.lore4);
        set_position_scale(3, 0, 0, data->sprites.menu.lore_sprites.lore5);
        set_position_scale(3, 0, 0, data->sprites.menu.lore_sprites.lore6);
        set_position_scale(3, 0, 0, data->sprites.menu.lore_sprites.lore7);
        set_position_scale(3, 0, 0, data->sprites.menu.lore_sprites.lore8);
        set_position_scale(3, 0, 0, data->sprites.menu.lore_sprites.lore9);
    } else
        set_fullscreen_pause(data);
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
    if (data->game_time > 21.0 && data->game_time < 30.0)
        sfRenderWindow_drawSprite(data->window,
    data->sprites.menu.lore_sprites.lore3, NULL);
}

static void display_lore_part2(data_t *data)
{
    if (data->game_time > 30.0 && data->game_time < 43.0)
        sfRenderWindow_drawSprite(data->window,
    data->sprites.menu.lore_sprites.lore4, NULL);
    if (data->game_time > 43.0 && data->game_time < 74.0)
        sfRenderWindow_drawSprite(data->window,
    data->sprites.menu.lore_sprites.lore5, NULL);
}

static void display_lore_part3(data_t *data)
{
    if (data->game_time > 74.0 && data->game_time < 82.0)
        sfRenderWindow_drawSprite(data->window,
    data->sprites.menu.lore_sprites.lore6, NULL);
    if (data->game_time > 82.0 && data->game_time < 90.0)
        sfRenderWindow_drawSprite(data->window,
    data->sprites.menu.lore_sprites.lore7, NULL);
    if (data->game_time > 90.0 && data->game_time < 96.0)
        sfRenderWindow_drawSprite(data->window,
    data->sprites.menu.lore_sprites.lore8, NULL);
    if (data->game_time > 96.0 && data->game_time < 109.0)
        sfRenderWindow_drawSprite(data->window,
    data->sprites.menu.lore_sprites.lore9, NULL);
}

void display_lore_dump(data_t *data)
{
    display_lore_part1(data);
    display_lore_part2(data);
    display_lore_part3(data);
    if (data->game_time == 109.0)
        data->scene = MENU;
}
