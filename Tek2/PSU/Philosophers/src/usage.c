/*
** EPITECH PROJECT, 2018
** Philosopher
** File description:
** usage.c
*/

#include <stdio.h>

//Prints an helper if the arguments are wrong
int print_helper(char *str)
{
	printf("USAGE\n");
	printf("\t%s -p nbr_p -e nbr_e\n\n", str);
	printf("DESCRIPTION\n");
	printf("\t -p nbr_p number of philosophers\n");
	printf("\t -e nbr_e maximum number times a philosopher eats");
	printf("before exiting the program\n");
	return 0;
}
