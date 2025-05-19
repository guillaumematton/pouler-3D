/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** create_environment_sprites
*/

#include "wolf3d.h"

bool create_env_sprite(data_t *data, const char *filename,
    sfSprite **adress_sprite)
{
    environment_texture_t **env_txt = &data->assets.environment_textures;
    environment_texture_t *env = *env_txt;
    sfSprite *sprite = sfSprite_create();

    if (!sprite)
        return true;
    for (; env != NULL && my_strcmp(env->name, filename) != 0;
            env = env->next);
    if (env == NULL) {
        if (data->arguments.debug)
            printf("Failed to load %s sprite. Aborting\n", filename);
        sfSprite_destroy(sprite);
        return true;
    }
    sfSprite_setTexture(sprite, env->texture, sfTrue);
    *adress_sprite = sprite;
    if (data->arguments.debug)
        printf("Loaded %s sprite.\n", filename);
    return false;
}

bool create_room_sprites(data_t *data)
{
    if (create_env_sprite(data, "J",
        &data->sprites.environment.ceiling))
        return true;
    if (create_env_sprite(data, "J",
        &data->sprites.environment.floor))
        return true;
    if (create_env_sprite(data, "J",
        &data->sprites.environment.walls))
        return true;
    return false;
}
