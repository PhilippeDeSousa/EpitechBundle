NAME		= 	mysh

CC			= 	gcc

RM			= 	rm -f

SRCS_DIR	= 	./src/

LIB_DIR 	=	./lib/

BUILT_DIR 	=	./builtin/

SRCS		=	main.c						\
				$(SRCS_DIR)get_next_line.c 	\
				$(SRCS_DIR)shell.c			\
				$(SRCS_DIR)cut_string.c		\
				$(SRCS_DIR)exec.c			\
				$(SRCS_DIR)parse_env.c		\
				$(SRCS_DIR)parse_input.c	\
				$(SRCS_DIR)interpretor.c	\
				$(SRCS_DIR)flags_handler.c	\
				$(SRCS_DIR)tree.c			\
				$(SRCS_DIR)set_commands.c	\
				$(BUILT_DIR)setenv.c		\
				$(BUILT_DIR)cd.c			\
				$(BUILT_DIR)unsetenv.c		\
				$(BUILT_DIR)exit.c			\
				$(LIB_DIR)strcmp.c			\
				$(LIB_DIR)arr_len.c			\
				$(LIB_DIR)str_to_array.c	\
				$(LIB_DIR)print_array.c		\
				$(LIB_DIR)strdup.c			\
				$(LIB_DIR)strcat.c			\
				$(LIB_DIR)free_array.c		\
				$(LIB_DIR)strncpy.c			\
				$(LIB_DIR)convertnb.c		\
				$(LIB_DIR)epur_str.c		\
				$(LIB_DIR)putstr.c

OBJS		= 	$(SRCS:.c=.o)

CFLAGS		+= 	-I./include -g3 -Wall -Wextra -pedantic

all		:	$(NAME)

$(NAME)		: 	$(OBJS)
			$(CC) -o $(NAME) $(OBJS) $(CFLAGS)

clean		:
			$(RM) $(OBJS)

fclean		:	clean
			$(RM) $(NAME)

re		:	fclean all
			$(RM) $(OBJS)

.PHONY		: 	all clean fclean re

