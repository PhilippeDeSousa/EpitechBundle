CPPFLAGS=		-Iinclude

CPFLAGS	= 		-Wall -Wextra -Werror

SRC	=	main.c					\
		src/sort.c				\
		src/c_library.c			\
		src/list_functions.c

OBJ	=	$(SRC:.c=.o)

NAME	=	push_swap

all: 	$(NAME)

$(NAME):	$(OBJ)
	gcc -Iinclude -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:	fclean all
	rm -f $(OBJ)

.PHONY: all clean fclean re
