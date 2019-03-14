##
## EPITECH PROJECT, 2018
## IA
## File description:
## Makefile
##

NAME		=		../zappy_ai

SRC		=		src/main.cpp			\
				src/Client.cpp			\
				src/Errors.cpp			\
				src/AIinit.cpp			\
				src/AIbehaviorModes.cpp		\
				src/AIcommands.cpp		\
				src/AIgathering.cpp		\
				src/AIincantation.cpp		\
				src/AIinterpret.cpp		\
				src/Inventory.cpp		\
				src/Vision.cpp			\
				src/ConnectionHandler.cpp

OBJS		= 		$(SRC:.cpp=.o)

CC		= 		g++

CXXFLAGS	+= 		-std=c++17 -Wall -Wextra -Werror -Iinclude/

RM		= 		rm -f

all: 				$(NAME)

$(NAME): 			$(OBJS)
				$(CC) -o $(NAME) $(OBJS) $(CXXFLAGS)

clean:
				$(RM) $(OBJS)

fclean: 			clean
				$(RM) $(NAME)

re: 				fclean all
				rm -rf $(OBJS)

.PHONY: 			all clean fclean re
