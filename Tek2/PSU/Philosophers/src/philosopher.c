/*
** EPITECH PROJECT, 2018
** Philosopher
** File description:
** philosopher.c
*/

#include "philosopher.h"

int turn = 0;

//Doesn't do anything: philosopher rests
void *philo_rest(t_philosopher *philo)
{
	if (philo->number % 2 != turn) {
		lphilo_sleep();
		philo->action = REST;
	}
	return NULL;
}

//Locks one chopstick to think
void *philo_think(t_philosopher *philo)
{
	if (pthread_mutex_trylock(&philo->mutex) == 0) {
		lphilo_take_chopstick(&philo->mutex);
		lphilo_think();
		lphilo_release_chopstick(&philo->mutex);
		pthread_mutex_unlock(&philo->mutex);
		philo->action = THINK;
	}
	else if (pthread_mutex_trylock(&philo->left->mutex) == 0) {
		lphilo_take_chopstick(&philo->mutex);
		lphilo_think();
		lphilo_release_chopstick(&philo->mutex);
		pthread_mutex_unlock(&philo->left->mutex);
		philo->action = THINK;
	}
	return NULL;
}

//Locks two chopsticks to eat
void *philo_eat(t_philosopher *philo)
{
	if (pthread_mutex_trylock(&philo->mutex) == 0) {
		pthread_mutex_lock(&philo->left->mutex);
		lphilo_take_chopstick(&philo->mutex);
		lphilo_take_chopstick(&philo->left->mutex);
		lphilo_eat();
		lphilo_release_chopstick(&philo->mutex);
		lphilo_release_chopstick(&philo->left->mutex);
		pthread_mutex_unlock(&philo->mutex);
		pthread_mutex_unlock(&philo->left->mutex);
		philo->hp -= 1;
		philo->action = EAT;
	}
	return NULL;
}

//Philosopher's loop: decides which action to make
void *philo_manager(void *arg)
{
	t_philosopher *philo = arg;

	while (philo->hp > 0) {
		if (philo->action == THINK && philo->number % 2 != turn) {
			philo_eat(philo);
			philo_rest(philo);
		}
		else if (philo->action == REST && philo->number % 2 != turn) {
			philo_think(philo);
			philo_eat(philo);
		}
		else
			philo_rest(philo);
		usleep(2000);
	}
	turn += 1;
	pthread_exit(NULL);
}

//Create every philosopher and assign their values
int create_philosophers(int nb_p, int nb_e)
{
	t_philosopher *philo = malloc(sizeof(t_philosopher) * nb_p);

	if (philo == NULL)
		return 84;
	for (int i = 0; i < nb_p; i++)
		if (pthread_mutex_init(&philo[i].mutex, NULL) != 0)
			return 84;
	for (int c = 0; c < nb_p; c++) {
		if (pthread_create(&philo[c].thread, NULL,
			philo_manager, &philo[c]) != 0)
				return 84;
		init_philosopher(&philo[c], c, nb_e);
		philo[c].left = &philo[(c - 1)];
	}
	philo[0].left = &philo[nb_p - 1];
	for (int j = 0; j < nb_p; j++)
		if (pthread_join(philo[j].thread, NULL) != 0)
			return 84;
	return 0;
}
