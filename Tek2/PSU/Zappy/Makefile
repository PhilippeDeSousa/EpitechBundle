##
## EPITECH PROJECT, 2018
## Zappy
## File description:
## Makefile
##

all:
				make -C ./src_server
				make -C ./client
				make -C ./graphic

zappy_server:
				make -C ./src_server

zappy_ai:
				make -C ./client


clean:
				make clean -C ./src_server
				make clean -C ./client
				make clean -C ./graphic

fclean:
				make fclean -C ./src_server
				make fclean -C ./client
				make fclean -C ./graphic

re:
				make re -C ./src_server
				make re -C ./client
				make re -C ./graphic

test_run:			all
				make -C tests

.PHONY: 			all zappy_server zappy_ai clean fclean
