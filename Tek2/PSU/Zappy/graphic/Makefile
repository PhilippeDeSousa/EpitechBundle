##
## EPITECH PROJECT, 2018
## Graphic
## File description:
## Makefile
##

NAME		=		../zappy_graphic_client

SRC		=		src/Client.cpp			\
				src/Graphic.cpp			\
				src/Errors.cpp

OBJS		= 		$(SRC:.cpp=.o)

CC		=		g++

CXXFLAGS	+= 		-std=c++17 -Wall -Wextra -Werror -Iinclude/

RM		= 		rm -f

all: 				$(NAME)

$(NAME): 			$(OBJS)
				$(CC) -o $(NAME) $(OBJS) $(CXXFLAGS) -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

clean:
				$(RM) $(OBJS)

fclean: 			clean
				$(RM) $(NAME)

re: 				fclean all
				rm -rf $(OBJS)

.PHONY: 			all clean fclean re
