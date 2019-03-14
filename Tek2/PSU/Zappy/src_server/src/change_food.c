/*
** EPITECH PROJECT, 2018
** Project description
** File description:
** Description here
*/

#include "server.h"

void add_fd(client_t *cl, int *taker, int *giver, server_t *serv)
{
	double diff;

	cl->cmd = 1;
	if (*giver > 0) {
		*taker += 1;
		*giver -= 1;
		diff = HEALTH_PER_FOOD / serv->freq * 1000000.0f;
		cl->lifetime += diff;
	} else
		cl->cmd = -1;
}

void rem_fd(client_t *cl, int *taker, int *giver, server_t *serv)
{
	double diff;

	cl->cmd = 1;
	if (*giver > 0) {
		*taker += 1;
		*giver -= 1;
		diff = HEALTH_PER_FOOD / serv->freq * 1000000.0f;
		cl->lifetime -= diff;
	} else
		cl->cmd = -1;
}
