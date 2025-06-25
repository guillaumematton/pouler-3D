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
    #include <string.h>

    #include "my.h"
    #include "sprite.h"
    #include "assets.h"

    #define GAME_FPS 60
    #define INTERNAL_WIDTH 800
    #define INTERNAL_HEIGHT 600

    #define DUST_PARTICULES_COUNT 200

typedef struct argument_s {
    bool help;
    bool full_screen;
    bool debug;
} arguments_t;

enum scene {
    MENU,
    MENU_OPTIONS,
    GAME_OPTIONS,
    LORE,
    GAME,
    PAUSE,
    WIN_SCREEN
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

typedef struct current_weapon_s {
    weapon_t *weapon;
    sfSprite *current_sprite;
    float time_to_wait;
} current_weapon_t;

typedef struct current_map_s {
    map_t *current_map;
    sfImage *walls_image;
    sfImage *ceil_image;
    sfImage *floor_image;
} current_map_t;

typedef struct dust_particule_s {
    float x_pos;
    float y_pos;
    float x_vel;
    float y_vel;
} dust_particule_t;

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
    sfImage *game_screen_image;
    sfTexture *game_screen_text;
    sfSprite *game_screen;
    sfVector2u screen_size;
    current_weapon_t current_weapon;
    current_map_t map;
    sfRectangleShape *tile;
    bool exit;
    sfEvent event;
    double game_time;
    float tick_duration;
    sfText *hud_text;
    float volume;
    int score;
    dust_particule_t dust_particules[200];
} data_t;

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
    unsigned int mapX;
    unsigned int mapY;
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
    unsigned int draw_end;
    float wallX;
} draw_info_t;

    #define TEX_SIZE 48

//init
data_t initialize_data(void);
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
void load_font(data_t *data, char *folder_path, char *asset_name);
void load_environment_texture(data_t *data, char *folder_path,
    char *asset_name);
bool bind_assets(data_t *data);
bool bind_weapon_assets(data_t *data);
void load_gui_texture(data_t *data, char *folder_path, char *asset_name);
void set_position_scale(float scale_value, float positionx,
    float positiony, sfSprite *sprite);

//main_loop
void run_main_loop(data_t *data);
void manage_music(data_t *data);
void manage_time(data_t *data);

//menu
void run_menu_scene(data_t *data);
void render_menu(data_t *data);
void handle_menu_interactions(data_t *data);
void start_new_game(data_t *data);

//options
void run_menu_options_scene(data_t *data);
void run_game_options_scene(data_t *data);
void render_options(data_t *data);
void handle_options_interactions(data_t *data);

//game
void run_game_scene(data_t *data);
bool set_new_map(data_t *data, char *name);
void render_game(data_t *data, map_t *map);
void handle_movement(char **map, data_t *data);
bool create_wall_images(data_t *data);
void set_sprite_positions(data_t *data);
void cast_floor_and_ceiling(data_t *data);
void handle_firearms(data_t *data);
void render_hud_text(data_t *data);
void draw_minimap(data_t *data);
void render_dust_particules(data_t *data);

//pause
void run_pause_scene(data_t *data);
void render_pause(data_t *data);
void handle_pause_interactions(data_t *data);

//win screen
void run_win_screen_scene(data_t *data);
void render_win_screen(data_t *data);

//term
void terminate_game(data_t *data);
void destroy_assets(data_t *data);

//lore
void display_lore_dump(data_t *data);
void browse_sounds(data_t *data);

//save
void save_game(data_t *data);
void load_game(data_t *data);

#endif
