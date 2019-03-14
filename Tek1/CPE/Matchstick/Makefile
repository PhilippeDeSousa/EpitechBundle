CPPFLAGS 	= 	-Iinclude

CFLAGS		= 	-Wall -Wextra

SRC 		= 	main.c						\
				src/get_next_line.c			\
				src/get_nbr.c				\
				src/matchstick.c			\
				src/display.c				\
				src/map_generator.c			\
				src/player.c				\
				src/common_functions.c		\
				src/ai.c

OBJ			= 	$(SRC:.c=.o)

NAME		= 	matchstick

all: 			$(NAME)

$(NAME):	 	$(OBJ)
			gcc -g3 -o $(NAME) $(OBJ)

clean:
			rm -f $(OBJ)

fclean: 	clean
			rm -f $(NAME)

re: 		fclean all clean
			rm -f $(OBJ)

.PHONY: 	all clean fclean re
