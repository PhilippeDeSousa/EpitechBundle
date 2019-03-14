##
## EPITECH PROJECT, 2018
## Bollinger
## File description:
## Makefile
##

NAME		=		bollinger

SRC		=		main.cpp		\
				src/bollinger.cpp	\
				src/errors.cpp

OBJS		= 		$(SRC:.cpp=.o)

CC		= 		g++

CPPFLAGS	+= 		-std=c++11 -Wall -Wextra -Iinclude/

RM		= 		rm -f

all: 				$(NAME)

$(NAME): 			$(OBJS)
				$(CC) -o $(NAME) $(OBJS) $(CPPFLAGS)

clean:
				$(RM) $(OBJS)

fclean: 			clean
				$(RM) $(NAME)

re: 				fclean all
				rm -rf $(OBJS)

.PHONY: 			all clean fclean re
