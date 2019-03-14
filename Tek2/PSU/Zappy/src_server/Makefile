##
## EPITECH PROJECT, 2018
## Zappy
## File description:
## Makefile
##

NAME		=		../zappy_server

SRC		=		main.c				\
				src/server.c			\
				src/create_server.c		\
				src/handle_client.c		\
				src/new_client.c		\
				src/read_line.c			\
				src/set_input.c			\
				src/getopt.c			\
				src/handle_mats.c		\
				src/make_connection.c		\
				src/moves.c			\
				src/ignore.c			\
				src/inventory.c			\
				src/elevation.c			\
				src/connect_number.c		\
				src/handle_time.c		\
				src/look.c			\
				src/print_item.c		\
				src/broadcast.c			\
				src/eject.c			\
				src/close_server.c		\
				src/fork.c			\
				src/change_food.c		\
				graphic/graphic_client.c	\
				graphic/send_map.c

OBJS		= 		$(SRC:.c=.o)

CC		= 		gcc

CFLAGS		+= 		-Wall -Wextra -Werror -Iinclude/

RM		= 		rm -f

all: 				$(NAME)

$(NAME): 			$(OBJS)
				$(CC) -o $(NAME) $(OBJS) $(CFLAGS)

clean:
				$(RM) $(OBJS)

fclean: 			clean
				$(RM) $(NAME)

re: 				fclean all
				rm -rf $(OBJS)

.PHONY: 			all clean fclean re
