/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** handle_firearms
*/

#include "wolf3d.h"

static void modify_sprite_for_idle(data_t *data)
{
    data->current_weapon.current_sprite =
        data->current_weapon.weapon->default_sprite;
    if (!data->current_weapon.current_sprite)
        return;
    if (!data->arguments.full_screen)
        set_position_scale(0.8, 250, 150, data->current_weapon.current_sprite);
    else
        set_position_scale(1.6, 600, 200, data->current_weapon.current_sprite);
}

static void modify_sprite_for_firing(data_t *data)
{
    data->current_weapon.current_sprite =
        data->current_weapon.weapon->fire_sprite;
    data->current_weapon.time_to_wait = data->current_weapon.weapon->firerate;
    if (!data->arguments.full_screen)
        set_position_scale(0.8, 250, 150, data->current_weapon.current_sprite);
    else
        set_position_scale(1.6, 600, 200, data->current_weapon.current_sprite);
    if (data->current_weapon.weapon->ammo > 0)
        data->current_weapon.weapon->ammo--;
    if (data->current_weapon.weapon->sound != NULL)
        sfSound_play(data->current_weapon.weapon->sound->sound);
}

static void change_weapon(data_t *data, int id)
{
    weapon_t *weapon_list = data->assets.weapons;

    for (int i = 1; weapon_list != NULL && i < id; i++)
        weapon_list = weapon_list->next;
    if (weapon_list == NULL ||
        data->current_weapon.weapon == weapon_list)
        return;
    data->current_weapon.weapon = weapon_list;
    data->current_weapon.current_sprite = weapon_list->default_sprite;
    data->current_weapon.time_to_wait = 0;
    if (!data->arguments.full_screen)
        set_position_scale(0.8, 250, 150, data->current_weapon.current_sprite);
    else
        set_position_scale(1.6, 600, 200, data->current_weapon.current_sprite);
}

static void handle_firearms_switch(data_t *data)
{
    if (data->current_weapon.weapon == NULL)
        change_weapon(data, 1);
    if (sfKeyboard_isKeyPressed(sfKeyNumpad1))
        change_weapon(data, 1);
    if (sfKeyboard_isKeyPressed(sfKeyNumpad2))
        change_weapon(data, 2);
    if (sfKeyboard_isKeyPressed(sfKeyNumpad3))
        change_weapon(data, 3);
    if (sfKeyboard_isKeyPressed(sfKeyNumpad4))
        change_weapon(data, 4);
    if (sfKeyboard_isKeyPressed(sfKeyNumpad5))
        change_weapon(data, 5);
}

static bool basic_check_for_firearms(data_t *data)
{
    static bool old_fscreen = false;

    if (old_fscreen != data->arguments.full_screen) {
        if (!data->current_weapon.current_sprite)
            return false;
        set_position_scale(1.6, 600, 200, data->current_weapon.current_sprite);
        old_fscreen = data->arguments.full_screen;
    }
    if (data->current_weapon.time_to_wait > 0) {
        data->current_weapon.time_to_wait -= data->tick_duration;
        if (data->current_weapon.time_to_wait < 0)
            data->current_weapon.time_to_wait = 0;
        else
            return true;
    }
    return false;
}

void handle_firearms(data_t *data)
{
    static bool is_firing = false;

    if (basic_check_for_firearms(data))
        return;
    while (is_firing == true && data->current_weapon.time_to_wait == 0) {
        is_firing = false;
        modify_sprite_for_idle(data);
        return;
    }
    handle_firearms_switch(data);
    if (sfMouse_isButtonPressed(sfMouseLeft) &&
        (data->current_weapon.weapon->ammo != 0 ||
        data->current_weapon.weapon->max_ammo == 0)) {
        is_firing = true;
        modify_sprite_for_firing(data);
    }
}
