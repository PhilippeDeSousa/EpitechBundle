##
## Makefile for  in /home/Wasx/CPool_Day12
## 
## Made by Wassim ALKAYAR
## Login   <Wasx@epitech.net>
## 
## Started on  Wed Mar 15 10:16:14 2017 Wassim ALKAYAR
## Last update Sun Oct  8 18:46:36 2017 Wassim Alkayar
##

NAME	=	42sh

SRC	=	main.c			\
		src/shell.c		\
		src/shell_tools.c	\
		src/basicfcts.c		\
		src/tools.c		\
		src/tools2.c		\
		src/tools3.c		\
		src/get_next_line.c	\
		src/check_commands.c	\
		src/check_commands2.c	\
		src/env.c		\
		src/setenv.c		\
		src/unsetenv.c		\
		src/parsing.c		\
		src/execve.c		\
		src/change_directory.c	\
		src/cd_utils.c		\
		src/exit.c		\
		src/right_redirections.c\
		src/left_redirections.c	\
		src/check_pipe.c	\
		src/simple_pipe.c	\
		src/multiple_pipes.c	\
		src/my_put_nbr.c	\
		src/my_strcat.c		\
		src/str_to_wordtab.c	\
		src/execute_alias.c	\
		src/tmp_alias.c		\
		src/globbing.c				\
		src/repeat.c

SRC2	=	src/linkedlists/linkedlists.c

OBJ	=	$(SRC:.c=.o) $(SRC2:.c=.o)

GCC	=	gcc

CFLAGS	=	-g3 -Wextra -Wall

CPPFLAGS=	-I./include

RM	=	rm -f

all: $(NAME)

$(NAME): $(OBJ)
	$(GCC) -o $(NAME) $(OBJ) $(CFLAGS) $(CPPFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re:	fclean all
	$(RM) $(OBJ)

.PHONY: all clean fclean re
