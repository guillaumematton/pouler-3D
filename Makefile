##
## EPITECH PROJECT, 2025
## wolf3d
## File description:
## Makefile
##

NAME	= wolf3d

SRC	= src/main.c\
	  src/check_if_in_gui.c\
	  src/parse_args.c\
	  src/initialize_game.c\
	  src/load_data.c\

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


all: libmy $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(WFLAGS)

debug: libmy_debug $(OBJ)
	$(CC) -o $(NAME)_debug $(OBJ) $(CFLAGS) -g $(WFLAGS)

clean:
	@cd lib/my ; make clean -s
	@rm -f $(OBJ)

fclean: clean
	@cd lib/my ; make fclean -s
	@rm -f $(NAME)
	@rm -f $(NAME)_debug

re: fclean all

tests_run: all

run: all
	./$(NAME)

libmy:
	@cd lib/my ; make -s

libmy_debug:
	@cd lib/my ; make debug -s

test: fclean debug
	valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all\
 ./$(NAME)_debug
