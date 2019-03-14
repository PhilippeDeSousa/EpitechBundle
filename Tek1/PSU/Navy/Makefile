##
## Makefile for navy in /home/philippe/PSU/PSU_2016_navy
## 
## Made by Philippe De Sousa
## Login   <philippe.de-sousa-violante@epitech.eu>
## 
## Started on  Tue Jun 27 12:35:41 2017 Philippe De Sousa
## Last update Thu Jul 13 21:11:14 2017 Wassim Alkayar
##

NAME	=	navy

GCC	=	gcc

SRC	=	main.c			\
		src/read.c		\
		src/get_next_line.c	\
		src/my_strcmp.c		\
		src/navy_man.c		\
		src/start_game.c	\
		src/convertnb.c		\
		src/start_game_tools.c	\
		src/start_game_tools2.c	\
		src/get_pos.c		\
		src/str_to_tab.c	\
		src/print_boats.c	\
		src/print_double_tab.c	\
		src/prepare_game.c	\
		src/server.c		\
		src/my_put_nbr.c	\
		src/check_map.c		\
		src/signal_next.c

OBJ	=	$(SRC:.c=.o) $(SRC2:.c=.o)

CFLAGS	= -Wall -Wextra

CPPFLAGS	=	-Iinclude

all: $(NAME)

$(NAME): $(OBJ)
	$(GCC) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)	

re: fclean all
	rm -f $(OBJ)

.PHONY:	all clean fclean re
