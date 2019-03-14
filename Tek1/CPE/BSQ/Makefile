##
## Makefile for BSQ in /home/philippe/Projects/CPE_2016_BSQ
## 
## Made by Philippe De Sousa
## Login   <philippe.de-sousa-violante@epitech.eu>
## 
## Started on  Tue May  2 14:35:16 2017 Philippe De Sousa
## Last update Sun May  7 22:38:46 2017 Philippe De Sousa
##

CPPFLAGS 	= 	-Iinclude

CFLAGS		= 	-Wall -Wextra

SRC 		= 	main.c				\
				src/basics.c		\
				src/bsq.c			\
				src/check_pos.c

OBJ			= 	$(SRC:.c=.o)

NAME		= 	bsq

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
