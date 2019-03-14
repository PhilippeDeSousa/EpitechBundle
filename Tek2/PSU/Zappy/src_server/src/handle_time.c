/*
** EPITECH PROJECT, 2018
** Project description
** File description:
** Description here
*/

#include "client.h"
#include <sys/time.h>
#include <stdlib.h>

/// Busy loop that waits
/// @param cl
void wait_timer(client_t *cl)
{
	while (cl->action > get_time(0.0f)) {
	}
}

/// get current time
/// @param timer (offset)
/// @return current time
double get_time(double timer)
{
	struct timeval tv;
	double retval;

	gettimeofday(&tv, NULL);
	retval = ((((double)tv.tv_sec) * 1000000.0f) + (((double)tv.tv_usec)));
	retval += (timer * 1000000.0f);
	return retval;
}

///
/// @param client
void get_life(client_t *client)
{
	struct timeval tv;
	double curtime;

	gettimeofday(&tv, NULL);
	curtime = ((((double)tv.tv_sec) * 1000000.0f) + (((double)tv.tv_usec)));
	(void)curtime;
	(void)client;
}

///
/// @param timer
/// @return
int get_food(double timer)
{
	return (int)(((timer - get_time(0.00f)) / 1000000.0f) / 1.26);
}
