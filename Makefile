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
	  src/menu/create_main_menu_sprites.c\

LIB	= lib/libmy.a\

OBJ	= $(SRC:.c=.o)

CC	= gcc

WFLAGS  = -Wall -Wextra -fanalyzer

CFLAGS	= -I include -L lib -l my -lm -l csfml-graphics\
	-l csfml-audio -l csfml-system -lm

ifeq ($(MAKECMDGOALS),debug)
    CFLAGS += -g
endif
ifeq ($(MAKECMDGOALS),test)
    CFLAGS += -g
endif


all: $(NAME)

debug: $(NAME)_debug

$(NAME): $(LIB) $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(WFLAGS)

$(NAME)_debug: $(LIB) $(OBJ)
	$(CC) -o $(NAME)_debug $(OBJ) $(CFLAGS) $(WFLAGS)

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
	./$(NAME)

$(LIB):
	@$(MAKE) -sC lib/my

test: debug
	valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all\
 ./$(NAME)_debug
