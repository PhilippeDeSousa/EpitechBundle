##
## Makefile for makefile in /home/Max/Documents/delivery/CPE_year_Pushswap
## 
## Made by fourrier maxence
## Login   <maxence.fourrier@epitech.eu>
## 
## Started on  Tue Apr 11 10:05:45 2017 fourrier maxence
## Last update Mon Sep 25 17:13:35 2017 Wassim Alkayar
##

NAME		= 	lem_in

CC		= 	gcc

RM		= 	rm -f

SRCS_DIR	= 	./src/

SRCS		=	$(SRCS_DIR)main.c			\
			$(SRCS_DIR)tools.c			\
			$(SRCS_DIR)init_road.c			\
			$(SRCS_DIR)print_lemin.c		\
			$(SRCS_DIR)init_room.c			\
			$(SRCS_DIR)check_buff.c			\
			$(SRCS_DIR)del_comment.c		\
			$(SRCS_DIR)del_space.c			\
			$(SRCS_DIR)del_line.c			\
			$(SRCS_DIR)tab_size.c			\
			$(SRCS_DIR)utils.c			\
			$(SRCS_DIR)init_val.c			\
			$(SRCS_DIR)my_strcat.c			\
			$(SRCS_DIR)get_road.c			\
			$(SRCS_DIR)get_buff.c			\
			$(SRCS_DIR)lemin.c			\
			$(SRCS_DIR)get_next_line.c		\
			$(SRCS_DIR)my_strdup.c			\
			$(SRCS_DIR)linkedlists.c		\
			$(SRCS_DIR)get_all_roads.c		\
			$(SRCS_DIR)int_to_str.c			\
			$(SRCS_DIR)get_pos.c			\
			$(SRCS_DIR)str_to_tab.c			\
			$(SRCS_DIR)ants.c			\
			$(SRCS_DIR)get_roads_tools.c		\
			$(SRCS_DIR)epur_road.c

OBJS		= 	$(SRCS:.c=.o)

CFLAGS		+= 	-I./include -g3 -Wall -Wextra

LDFLAGS		+=	-L./lib/my -lmy

all		:	$(NAME)

$(NAME)		: 	$(OBJS)
			make -C ./lib/my
			$(CC) -o $(NAME) $(OBJS) $(CFLAGS) $(LDFLAGS)

clean		:
			make clean -C ./lib/my
			$(RM) $(OBJS)

fclean		:	clean
			make fclean -C ./lib/my
			$(RM) $(NAME)

re		:	fclean all
			$(RM) $(OBJS)

.PHONY		: 	all clean fclean re

