/*
** EPITECH PROJECT, 2018
** Philosopher
** File description:
** philosopher.c
*/

#include "philosopher.h"

//Initialises philosopher's values
void init_philosopher(t_philosopher *philo, int c, int nb_e)
{
	philo->number = c;
	philo->hp = nb_e;
	philo->action = (rand() % 3)  + 4;
}
