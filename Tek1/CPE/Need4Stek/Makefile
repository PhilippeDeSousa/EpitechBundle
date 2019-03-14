##
## Makefile for n4s in /home/philippe/CPE/CPE_2016_n4s/tmp/Need4Stek-master
## 
## Made by Philippe De Sousa
## Login   <philippe.de-sousa-violante@epitech.eu>
## 
## Started on  Sat Oct 14 06:25:01 2017 Philippe De Sousa
## Last update Sun Oct 15 15:25:58 2017 Philippe De Sousa
##

NAME		= ia

SRC		=		main.c			\
				src/get_next_line.c 	\
				src/move_car.c 		\
				src/str_to_tab.c 	\
				src/basics.c 		\
				src/dir.c 		\
				src/get_speed.c 	\
				src/end.c 		\
				src/rm_dots.c	 	\
				src/exec.c

OBJS		= 		$(SRC:.c=.o)

CC		= 		gcc

CFLAGS		+= 		-Wall -Wextra

CPPFLAGS	=		-I./include

RM		= rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(CFLAGS) $(CPPFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
	rm -rf $(OBJS)

.PHONY: all clean fclean re
