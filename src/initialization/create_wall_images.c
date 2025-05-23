/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** create_wall_images
*/

#include "wolf3d.h"

static bool create_env_images(const char *name,
    sfTexture *texture, env_t **images_adress)
{
    env_t *node = malloc(sizeof(env_t));

    if (!node)
        return true;
    node->image = sfTexture_copyToImage(texture);
    if (!node->image) {
        free(node);
        return true;
    }
    node->name = (char *)name;
    node->next = *images_adress;
    *images_adress = node;
    return false;
}

bool create_wall_images(data_t *data)
{
    environment_texture_t *env = data->assets.environment_textures;

    for (; env != NULL; env = env->next) {
        if (create_env_images(env->name,
            env->texture, &data->sprites.environment))
            return true;
    }
    return false;
}
