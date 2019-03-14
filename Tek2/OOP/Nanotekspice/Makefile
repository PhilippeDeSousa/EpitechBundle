##
## EPITECH PROJECT, 2018
##
## File description:
##
##

NAME		=		nanotekspice

SRC		=		main.cpp		\
				src/nanotekspice.cpp	\
				src/config.cpp		\
				src/input.cpp		\
				src/output.cpp		\
				src/clock.cpp		\
				src/false.cpp		\
				src/true.cpp		\
				src/4008.cpp		\
				src/4081.cpp		\
				src/errors.cpp		\
				src/4071.cpp		\
				src/4011.cpp		\
				src/4001.cpp 		\
				src/4030.cpp		\
				src/4069.cpp 		\
				src/4040.cpp 		\
				src/4017.cpp  		\
				src/4094.cpp 		\
				src/4514.cpp 		\
				src/4013.cpp 

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
