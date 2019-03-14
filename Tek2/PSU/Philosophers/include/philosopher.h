/*
** EPITECH PROJECT, 2018
** Philosopher
** File description:
** Header
*/

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include "extern.h"

# define REST 4
# define EAT 5
# define THINK 6

typedef struct          s_philosopher
{
	int                     number;
	int                     hp;
	int                     action;
	pthread_t               thread;
	pthread_mutex_t         mutex;
	struct s_philosopher    *left;
}                       t_philosopher;

int print_helper(char *);
int create_philosophers(int, int);
void init_philosopher(t_philosopher *, int, int);

#endif /* PHILOSOPHER_H */
