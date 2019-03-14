##
## EPITECH PROJECT, 2018
## FTP
## File description:
## Makefile
##

NAME		=		server

SRC		=		main.c				\
				src/create_server.c		\
				src/display.c			\
				src/handle_client.c		\
				src/login.c			\
				src/read_line.c			\
				src/ignore.c			\
				src/dir.c			\
				src/list.c			\
				src/data_transfer_pass.c	\
				src/data_transfer_act.c		\
				src/download.c			\
				src/upload.c			\
				src/delete.c			\
				src/unknown_command.c

OBJS		= 		$(SRC:.c=.o)

CC		= 		gcc

CFLAGS		+= 		-Wall -Wextra -Iinclude/ -pedantic -g3

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
