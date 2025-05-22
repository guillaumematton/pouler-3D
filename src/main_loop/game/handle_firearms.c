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
    set_position_scale(0.8, 250, 120, data->current_weapon.current_sprite);
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
    set_position_scale(0.8, 350, 120, data->current_weapon.current_sprite);
}

static void change_weapon(data_t *data, int id)
{
    weapon_t *weapon_list = data->assets.weapons;
    sfIntRect rect = {0, 0, 0, 0};
    sfIntRect reference = {0, 0, 0, 0};

    for (int i = 1; weapon_list != NULL &&
        i < id; i++)
    if (weapon_list == NULL)
        return;
    data->current_weapon.weapon = weapon_list;
    data->current_weapon.current_sprite = weapon_list->sprite;
    data->current_weapon.time_to_wait = 0;
    if (!data->current_weapon.current_sprite)
        return;
    reference = sfSprite_getTextureRect(weapon_list->sprite);
    data->current_weapon.sprite_size = sfIntRect_getSize(&reference);
    rect.left = 0;
    rect.top = 0;
    rect.width = data->current_weapon.sprite_size.x / 2;
    rect.height = data->current_weapon.sprite_size.y;
    sfSprite_setTextureRect(data->current_weapon.current_sprite, rect);
    set_position_scale(0.8, 250, 120, data->current_weapon.current_sprite);
}

static void handle_firearms_switch(data_t *data)
{
    if (data->current_weapon.weapon == NULL)
        change_weapon(data, 1);
    if (sfKeyboard_isKeyPressed(sfKeyNum1))
        change_weapon(data, 1);
    if (sfKeyboard_isKeyPressed(sfKeyNum2))
        change_weapon(data, 2);
    if (sfKeyboard_isKeyPressed(sfKeyNum3))
        change_weapon(data, 3);
    if (sfKeyboard_isKeyPressed(sfKeyNum4))
        change_weapon(data, 4);
    if (sfKeyboard_isKeyPressed(sfKeyNum5))
        change_weapon(data, 5);
}

void handle_firearms(data_t *data)
{
    static bool is_firing = false;

    if (data->current_weapon.time_to_wait > 0) {
        data->current_weapon.time_to_wait -= data->tick_duration;
        if (data->current_weapon.time_to_wait < 0)
            data->current_weapon.time_to_wait = 0;
        else
            return;
    }
    while (is_firing == true && data->current_weapon.time_to_wait == 0) {
        is_firing = false;
        modify_sprite_for_idle(data);
        return;
    }
    handle_firearms_switch(data);
    if (sfMouse_isButtonPressed(sfMouseLeft)) {
        is_firing = true;
        modify_sprite_for_firing(data);
    }
}
