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

enum scene {
    MENU,
    OPTIONS,
    GAME,
    PAUSE
};

typedef struct Player_s {
    float health;
    float x;
    float y;
    float dirX;
    float dirY;
    float planeX;
    float planeY;
} Player_t;

typedef struct data {
    arguments_t arguments;
    Player_t player;
    sfClock *clock;
    assets_t assets;
    sprite_t sprites;
    sfRenderWindow *window;
    sfMusic *current_music;
    char *current_music_name;
    enum scene scene;
    sfVertexArray *game_vertex;
    sfVector2u screen_size;
    bool exit;
    sfEvent event;
} data_t;

typedef struct current_level_s {
    map_t *current_map;
    sfImage *floor;
    sfImage *ceiling;
    sfImage *walls;
} current_level_t;

typedef struct ray_s {
    float rayDirX0;
    float rayDirY0;
    float rayDirX1;
    float rayDirY1;
    float rowDistance;
    float stepX;
    float stepY;
    float floorX;
    float floorY;
} ray_t;

typedef struct dist_info_s {
    int mapX;
    int mapY;
    int texX;
    int texY;
    float deltaDistX;
    float deltaDistY;
    float perpWallDist;
    float sideDistX;
    float sideDistY;
    int side;
    int hit;
} dist_info_t;

typedef struct draw_info_s {
    int texX;
    int line_height;
    int draw_start;
    int draw_end;
    float wallX;
} draw_info_t;

    #define TILE_SIZE 64
    #define TEX_SIZE 48

//init
bool check_if_in_gui(char **env);
bool parse_args(data_t *data, char **av);
bool display_help(data_t *data);
bool create_menu_sprites(data_t *data);
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

//main_loop
void run_main_loop(data_t *data);
void manage_music(data_t *data);

//menu
void run_menu_scene(data_t *data);
void render_menu(data_t *data);
void handle_menu_interactions(data_t *data);

//options
void run_options_scene(data_t *data);

//game
void run_game_scene(data_t *data);
void render_map(data_t *data);
void handle_movement(char **map, data_t *data);
bool create_wall_images(data_t *data);
void set_sprite_positions(data_t *data);
void cast_floor_and_ceiling(data_t *data);

//pause
void run_pause_scene(data_t *data);

//term
void terminate_game(data_t *data);
void destroy_assets(data_t *data);

#endif
