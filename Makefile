##
## EPITECH PROJECT, 2025
## wolf3d
## File description:
## Makefile
##

NAME	= wolf3d

## the sources files should be ordered by order of use in the program
SRC	= src/main.c\
	  src/initialize_data.c\
	  src/miscellaneous/check_if_in_gui.c\
	  src/initialization/parse_args.c\
	  src/miscellaneous/display_help.c\
	  src/initialization/initialize_game.c\
	  src/initialization/load_assets.c\
	  src/initialization/load_assets_folder.c\
	  src/initialization/load_sound.c\
	  src/initialization/create_wall_images.c\
	  src/initialization/load_music.c\
	  src/initialization/load_enemy_type.c\
	  src/initialization/load_map.c\
	  src/initialization/load_weapon.c\
	  src/initialization/load_entity_texture.c\
	  src/initialization/load_environment_texture.c\
	  src/initialization/load_gui_texture.c\
	  src/initialization/load_font.c\
	  src/initialization/bind_assets.c\
	  src/initialization/bind_weapon_assets.c\
	  src/initialization/create_menu_sprites.c\
	  src/main_loop/run_main_loop.c\
	  src/main_loop/manage_music.c\
	  src/main_loop/manage_time.c\
	  src/main_loop/menu/run_menu_scene.c\
	  src/main_loop/menu/render_menu.c\
	  src/main_loop/menu/handle_menu_interactions.c\
	  src/main_loop/menu/start_new_game.c\
	  src/main_loop/lore/lore_dump.c\
	  src/main_loop/options/run_options_scene.c\
	  src/main_loop/options/render_options.c\
	  src/main_loop/options/handle_options_interactions.c\
	  src/main_loop/game/floor_and_ceiling_rendering.c\
	  src/main_loop/game/handle_firearms.c\
	  src/main_loop/game/run_game_scene.c\
	  src/main_loop/game/renderer.c\
	  src/main_loop/game/player_movement.c\
	  src/main_loop/game/render_hud_text.c\
	  src/main_loop/game/draw_minimap.c\
	  src/main_loop/game/render_dust_particules.c\
	  src/main_loop/pause/run_pause_scene.c\
	  src/main_loop/pause/render_pause.c\
	  src/main_loop/pause/handle_pause_interactions.c\
	  src/main_loop/pause/save_game.c\
	  src/main_loop/menu/load_game.c\
	  src/main_loop/win_screen/run_win_screen_scene.c\
	  src/main_loop/win_screen/render_win_screen.c\
	  src/termination/terminate_game.c\
	  src/termination/destroy_assets.c\

OBJ	= $(SRC:.c=.o)

TESTS_SRC = tests/test_wolf3d.c

TESTS_OBJ = $(TESTS_SRC:.c=.o)

LIB	= lib/libmy.a\

CC	= gcc

WFLAGS	= -Wall -Wextra -fanalyzer

CFLAGS	= -I include -L lib -l my -lm -l csfml-graphics\
	-l csfml-audio -l csfml-system -l csfml-window


all: $(NAME)

$(NAME): $(LIB) $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(WFLAGS)

debug: CFLAGS += -g
debug: $(NAME)_debug

$(NAME)_debug: fclean
	make $(LIB)
	$(CC) -o $(NAME)_debug $(SRC) $(CFLAGS) $(WFLAGS)

$(LIB):
	@$(MAKE) -sC lib/my

clean:
	@$(MAKE) clean -sC lib/my
	@cd lib/my ; make clean -s
	@rm -f $(OBJ)

fclean: clean clean_tests
	@$(MAKE) fclean -sC lib/my
	@rm -f $(NAME)
	@rm -f $(NAME)_debug

clean_tests:
	@rm -f $(NAME)_test
	@rm -f *.gcda
	@rm -f *.gcno

re: fclean all

unit_tests: $(LIB)
	$(CC) $(filter-out src/main.c,$(SRC)) $(TESTS_SRC) $(CFLAGS) \
-o $(NAME)_test --coverage -lcriterion

tests_run: clean_tests unit_tests
	./$(NAME)_test || true
	gcovr --exclude tests/
	gcovr --exclude tests/ --txt-metric=branch || true

run: all
	./$(NAME) -d

test: debug
	valgrind \
--track-origins=yes \
--leak-check=full \
--show-leak-kinds=all \
--suppressions=valgrind_suppression \
./$(NAME)_debug -d
