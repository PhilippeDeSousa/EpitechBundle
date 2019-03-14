##
## EPITECH PROJECT, 2018
## Philosopher
## File description:
## Makefile
##

NAME		=		philo

SRC		=		main.c			\
				src/usage.c		\
				src/philosopher.c	\
				src/init.c

OBJS		= 		$(SRC:.c=.o)

CC		= 		gcc

CFLAGS		+= 		-Wall -Wextra -Iinclude/

LDFLAGS		=		-lpthread

RM		= 		rm -f

all: 				$(NAME)

$(NAME): 			$(OBJS)
				$(CC) -o $(NAME) $(OBJS) $(CFLAGS) libriceferee.so $(LDFLAGS)

clean:
				$(RM) $(OBJS)

fclean: 			clean
				$(RM) $(NAME)

re: 				fclean all
				rm -rf $(OBJS)

.PHONY: 			all clean fclean re
