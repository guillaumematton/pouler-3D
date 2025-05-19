##
## EPITECH PROJECT, 2025
## wolf3d
## File description:
## Makefile
##

NAME	= wolf3d

## the sources files should be ordered by order of use in the program
SRC	= src/main.c\
	  src/miscellaneous/check_if_in_gui.c\
	  src/initialization/parse_args.c\
	  src/miscellaneous/display_help.c\
	  src/initialization/initialize_game.c\
	  src/initialization/load_assets.c\
	  src/initialization/load_assets_folder.c\
	  src/initialization/load_sound.c\
	  src/initialization/load_music.c\
	  src/initialization/load_enemy_type.c\
	  src/initialization/load_map.c\
	  src/initialization/load_weapon.c\
	  src/initialization/load_entity_texture.c\
	  src/initialization/load_environment_texture.c\
	  src/initialization/load_gui_texture.c\
	  src/main_loop/run_loop.c\
	  src/main_loop/manage_music.c\
	  src/termination/terminate_game.c\
	  src/termination/destroy_assets.c\
	  src/menu/in_menu.c\
	  src/initialization/create_menu_sprites.c\
	  src/initialization/create_environment_sprites.c\
	  src/main_loop/renderer.c\
	  src/main_loop/floor_casting.c\
	  src/main_loop/player_movement.c\

LIB	= lib/libmy.a\

OBJ	= $(SRC:.c=.o)

CC	= gcc

WFLAGS  = -Wall -Wextra -fanalyzer

CFLAGS	= -I include -L lib -l my -lm -l csfml-graphics\
	-l csfml-audio -l csfml-system -l csfml-window


all: $(NAME)

$(NAME): $(LIB) $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(WFLAGS)

debug: CFLAGS += -g
debug: $(NAME)_debug

$(NAME)_debug: $(LIB) $(OBJ)
	$(CC) -o $(NAME)_debug $(OBJ) $(CFLAGS) $(WFLAGS)

$(LIB):
	@$(MAKE) -sC lib/my

clean:
	@$(MAKE) clean -sC lib/my
	@cd lib/my ; make clean -s
	@rm -f $(OBJ)

fclean: clean
	@$(MAKE) fclean -sC lib/my
	@rm -f $(NAME)
	@rm -f $(NAME)_debug

re: fclean all

run: all
	./$(NAME) -d

test: debug
	valgrind \
--track-origins=yes \
--leak-check=full \
--show-leak-kinds=all \
--suppressions=valgrind_suppression \
./$(NAME)_debug -d
