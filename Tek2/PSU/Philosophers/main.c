/*
** EPITECH PROJECT, 2018
** Philosopher
** File description:
** main.c
*/

#include "philosopher.h"
#include <time.h>

//Checks if the arguments are correct
int init_args(int ac, char **av, int *nb_p, int *nb_e)
{
	if (ac != 5)
		return 84;
	for (int i = 0; i < ac; i++) {
		if (strcmp(av[i], "-p") == 0 && av[i + 1])
			*nb_p = atoi(av[i + 1]);
		else if (strcmp(av[i], "-e") == 0 && av[i + 1])
			*nb_e = atoi(av[i + 1]);
	}
	for (int i = 0; i < ac; i++)
		if (strcmp(av[i], "--help") == 0)
			return 84;
	if (*nb_p < 1 || *nb_e < 1)
		return 84;
	return 0;
}

int main(int ac, char **av)
{
	int nb_p = 0;
	int nb_e = 0;
	int ret_val;

	srand(time(NULL));
	RCFStartup(ac, av);
	if (init_args(ac, av, &nb_p, &nb_e) != 0)
		return print_helper(av[0]);
	ret_val = create_philosophers(nb_p, nb_e);
	RCFCleanup();
	return ret_val;
}
