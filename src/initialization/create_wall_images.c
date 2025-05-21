/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** create_wall_images
*/

#include "wolf3d.h"

static bool create_env_images(data_t *data, const char *filename,
    sfImage **adress_image)
{
    environment_texture_t **env_txt = &data->assets.environment_textures;
    environment_texture_t *env = *env_txt;
    sfImage *image = NULL;

    for (; env != NULL && my_strcmp(env->name, filename) != 0;
        env = env->next);
    if (env == NULL) {
        if (data->arguments.debug)
            printf("Failed to load %s sprite. Aborting\n", filename);
        return true;
    }
    image = sfTexture_copyToImage(env->texture);
    *adress_image = image;
    if (data->arguments.debug)
        printf("Loaded %s Image.\n", filename);
    return false;
}

static bool create_more_wall_images(data_t *data)
{
    if (create_env_images(data, "F.png",
        &data->sprites.environment.F) ||
        create_env_images(data, "G.png",
        &data->sprites.environment.G) ||
        create_env_images(data, "H.png",
        &data->sprites.environment.H) ||
        create_env_images(data, "I.png",
        &data->sprites.environment.I))
        return true;
    return false;
}

bool create_wall_images(data_t *data)
{
    if (create_env_images(data, "A.png",
        &data->sprites.environment.A) ||
        create_env_images(data, "B.png",
        &data->sprites.environment.B) ||
        create_env_images(data, "C.png",
        &data->sprites.environment.C) ||
        create_env_images(data, "D.png",
        &data->sprites.environment.D) ||
        create_env_images(data, "E.png",
        &data->sprites.environment.E) ||
        create_more_wall_images(data))
        return true;
    return false;
}
