##
## EPITECH PROJECT, 2018
## MinilibC
## File description:
## Makefile
##

NAME		=	libasm.so

SRCS		=	src/strcmp.asm		\
			src/strlen.asm		\
			src/strncmp.asm		\
			src/strchr.asm		\
			src/memset.asm		\
			src/memcpy.asm		\
			src/memmove.asm		\
			src/strcasecmp.asm		\
			src/strpbrk.asm		\
			src/rindex.asm		\
			src/strcspn.asm		\
			src/strstr.asm


ASMFLAGS	=	-f elf64

LDFLAGS		=	-shared

ASM		=	nasm

CC		=	ld

RM		=	rm -f

OBJS		=	$(SRCS:.asm=.o)

%.o: 		%.asm
		$(ASM) -o $@ $< $(ASMFLAGS)

all:		$(NAME)

$(NAME):	$(OBJS)
		$(CC) $(LDFLAGS) -o $(NAME) $(OBJS)

test_runs:
		gcc tests/criterion.c libasm.so -o unit_test -lcriterion --coverage

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all
		$(RM) $(OBJS)

.PHONY: all clean fclean re
