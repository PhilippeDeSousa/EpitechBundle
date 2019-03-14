/*
** EPITECH PROJECT, 2018
** Project description
** File description:
** Description here
*/

#include "server.h"

void add(client_t *cl, int *taker, int *giver)
{
	cl->cmd = 1;
	if (*giver > 0) {
		*taker += 1;
		*giver -= 1;
	} else
		cl->cmd = -1;
}

void add_to_common_inv(client_t *cl, double freq,
	char *object, server_t *serv)
{
	inventory_t *cb = &serv->map[cl->y][cl->x].inv;
	!strcmp(object, "linemate") ? add(cl, &cb->l, &cl->inv.l) : ignore();
	!strcmp(object, "deraumere") ? add(cl, &cb->d, &cl->inv.d) : ignore();
	!strcmp(object, "sibur") ? add(cl, &cb->s, &cl->inv.s) : ignore();
	!strcmp(object, "mendiane") ? add(cl, &cb->m, &cl->inv.m) : ignore();
	!strcmp(object, "phiras") ? add(cl, &cb->p, &cl->inv.p) : ignore();
	!strcmp(object, "thystame") ? add(cl, &cb->t, &cl->inv.t) : ignore();
	!strcmp(object, "food") ?
		rem_fd(cl, &cb->f, &cl->inv.f, serv) : ignore ();
	cl->action = get_time((double)7.00f / freq);
	wait_timer(cl);
	cl->cmd == 1 ? dprintf(cl->sock, "ok\n") : ignore();
}

/// adds the object to the inventory of a client
/// @param cl
/// @param freq
/// @param object
/// @param serv

void add_to_client_inv(client_t *cl, double freq,
	char *object, server_t *serv)
{
	inventory_t *cb = &serv->map[cl->y][cl->x].inv;
	!strcmp(object, "linemate") ? add(cl, &cl->inv.l, &cb->l) : ignore();
	!strcmp(object, "deraumere") ? add(cl, &cl->inv.d, &cb->d) : ignore();
	!strcmp(object, "sibur") ? add(cl, &cl->inv.s, &cb->s) : ignore();
	!strcmp(object, "mendiane") ? add(cl, &cl->inv.m, &cb->m) : ignore();
	!strcmp(object, "phiras") ? add(cl, &cl->inv.p, &cb->p) : ignore();
	!strcmp(object, "thystame") ? add(cl, &cl->inv.t, &cb->t) : ignore();
	!strcmp(object, "food") ?
		add_fd(cl, &cl->inv.f, &cb->f, serv) : ignore ();
	cl->action = get_time((double)7.00f / freq);
	wait_timer(cl);
	srand(SEED);
	cl->cmd == 1 ? dprintf(cl->sock, "ok\n") : ignore();
	set_mat(serv, rand() % serv->width, rand() % serv->height);
}

/// Takes an object that is on a tile
/// @param serv
/// @param cl
/// @param input

void take_object(server_t *serv, client_t *cl, char *input)
{
	char *cmd;
	char *object;

	cmd = strtok(input, " ");
	object = strtok(NULL, " ");
	if (strcmp(cmd, "Set") == 0 && object != NULL)
		add_to_common_inv(cl,
			serv->freq, object, serv);
	else if (strcmp(cmd, "Take") == 0 && object != NULL)
		add_to_client_inv(cl,
			serv->freq, object, serv);
}
