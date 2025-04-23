/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** main header
*/

#ifndef WOLF3D
    #define WOLF3D

    #include <SFML/System.h>
    #include <SFML/Window.h>
    #include <SFML/Graphics.h>
    #include <SFML/Audio.h>
    #include <SFML/Window.h>
    #include <SFML/Window.h>
    #include <SFML/Graphics.h>
    #include <SFML/Window/Event.h>
    #include <SFML/Audio.h>
    #include <math.h>
    #include <time.h>

    #include "my.h"
    #include "sprite.h"
    #include "assets.h"

typedef struct argument_s {
    bool help;
    bool full_screen;
    bool debug;
} arguments_t;

typedef struct Player_s {
    float health;
    float x;
    float y;
    float angle;
} Player_t;

typedef struct data {
    arguments_t arguments;
    assets_t assets;
    sprite_t sprites;
    sfRenderWindow *window;
    sfMusic *current_music; //will have to be migrated someday
} data_t;

    #define TILE_SIZE 64

//void load_map(char *filename); //name conflict
//void init_player(Player_t *player);
//int is_wall(int x, int y);
//void print_help(void);

int main(int ac, char **av, char **env);
bool check_if_in_gui(char **env);
bool parse_args(data_t *data, char **av);
bool display_help(data_t *data);

bool initialize_game(data_t *data);
bool load_assets(data_t *data);
void load_assets_folder(data_t *data, char *module_path, char *folder_name,
    void (*load_asset)(data_t *data, char *folder_path, char *asset_name));
void load_sound(data_t *data, char *folder_path, char *asset_name);
void load_music(data_t *data, char *folder_path, char *asset_name);
void load_enemy_type(data_t *data, char *folder_path, char *asset_name);
void load_map(data_t *data, char *folder_path, char *asset_name);
void load_weapon(data_t *data, char *folder_path, char *asset_name);
void load_entity_texture(data_t *data, char *folder_path, char *asset_name);
void load_environment_texture(data_t *data, char *folder_path,
    char *asset_name);
void load_gui_texture(data_t *data, char *folder_path, char *asset_name);

void run_loop(data_t *data);
void manage_music(data_t *data);

void terminate_game(data_t *data);
void destroy_assets(data_t *data);

bool in_menu(data_t *data);
bool create_menu_background(data_t *data);

/*
void free_map_and_weapons(data_t *data);
void free_enemy_types(data_t *data);
void free_effects_and_entities(data_t *data);
void free_gui_and_environment_texture(data_t *data);
void destroy_window_and_music(data_t *data);
*/
#endif
