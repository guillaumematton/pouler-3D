/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** handle_firearms
*/

#include "wolf3d.h"

static void modify_sprite_for_idle(data_t *data)
{
    sfIntRect rect = {0, 0, 0, 0};

    if (!data->current_weapon.current_sprite)
        return;
    rect.left = 0;
    rect.top = 0;
    rect.width = data->current_weapon.sprite_size.x / 2;
    rect.height = data->current_weapon.sprite_size.y;
    data->current_weapon.current_sprite = data->current_weapon.weapon->sprite;
    if (!data->arguments.full_screen)
        set_position_scale(0.8, 250, 150, data->current_weapon.current_sprite);
    else
        set_position_scale(1.6, 600, 200, data->current_weapon.current_sprite);
    sfSprite_setTextureRect(data->current_weapon.current_sprite, rect);
}

static void modify_sprite_for_firing(data_t *data)
{
    sfIntRect rect = {0, 0, 0, 0};

    rect.left = data->current_weapon.sprite_size.x / 2;
    rect.top = 0;
    rect.width = data->current_weapon.sprite_size.x;
    rect.height = data->current_weapon.sprite_size.y;
    data->current_weapon.current_sprite = data->current_weapon.weapon->sprite;
    sfSprite_setTextureRect(data->current_weapon.current_sprite, rect);
    data->current_weapon.time_to_wait = data->current_weapon.weapon->firerate;
    if (!data->arguments.full_screen)
        set_position_scale(0.8, 250, 150, data->current_weapon.current_sprite);
    else
        set_position_scale(1.6, 600, 200, data->current_weapon.current_sprite);
    if (data->current_weapon.weapon->ammo > 0)
        data->current_weapon.weapon->ammo--;
}

static sfIntRect get_sprite_rect(data_t *data, weapon_t *weapon_list)
{
    sfIntRect reference = {0, 0, 0, 0};
    sfIntRect rect = {0, 0, 0, 0};

    reference = sfSprite_getTextureRect(weapon_list->sprite);
    data->current_weapon.sprite_size.x = reference.width;
    data->current_weapon.sprite_size.y = reference.height;
    rect.left = 0;
    rect.top = 0;
    rect.width = data->current_weapon.sprite_size.x / 2;
    rect.height = data->current_weapon.sprite_size.y;
    return rect;
}

static void change_weapon(data_t *data, int id)
{
    weapon_t *weapon_list = data->assets.weapons;
    sfIntRect rect = {0, 0, 0, 0};

    for (int i = 1; weapon_list != NULL && i < id; i++)
        weapon_list = weapon_list->next;
    if (weapon_list == NULL ||
        data->current_weapon.weapon == weapon_list)
        return;
    data->current_weapon.weapon = weapon_list;
    data->current_weapon.current_sprite = weapon_list->sprite;
    data->current_weapon.time_to_wait = 0;
    if (!data->current_weapon.current_sprite)
        return;
    rect = get_sprite_rect(data, weapon_list);
    sfSprite_setTextureRect(data->current_weapon.current_sprite, rect);
    if (data->arguments.full_screen == false)
        set_position_scale(0.8, 250, 150, data->current_weapon.current_sprite);
    else
        set_position_scale(0.8, 600, 200, data->current_weapon.current_sprite);
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

static void resize_sprite(data_t *data)
{
    set_position_scale(1.6, 600, 200, data->current_weapon.current_sprite);
}

static bool basic_check_for_firearms(data_t *data)
{
    static bool old_fscreen = false;

    if (old_fscreen != data->arguments.full_screen) {
        resize_sprite(data);
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
