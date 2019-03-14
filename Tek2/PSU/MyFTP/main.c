/*
** EPITECH PROJECT, 2018
** FTP
** File description:
** main.c
*/

#include "my_ftp.h"
#include <string.h>

static int check_args(int ac, char **av)
{
	if (ac != 3)
		return 1;
	for (int i = 0; i < ac; i++) {
		if (strcmp(av[i], "-help") == 0)
			return 1;
	}
	return 0;
}

static int usage(char *str)
{
	printf("%s -help\n", str);
	printf("USAGE:  %s port path\n", str);
	printf("\tport is the port number on");
	printf(" which the server socket listens\n");
	printf("\tpath is the path to the home");
	printf("directory for the Anonymous user\n");
	return 0;
}

int main(int ac, char **av)
{
	if (check_args(ac, av) != 0)
		return usage(av[0]);
	else
		return create_server(atoi(av[1]), av[2]);
}
