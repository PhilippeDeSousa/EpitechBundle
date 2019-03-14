/*
** EPITECH PROJECT, 2018
** cpp
** File description:
** cpp
*/

#include "server.h"

int check_team(server_t *sv, client_t *client)
{
	for (int x = 0; x < sv->nb_teams; x++) {
		if (sv->teams[x].id == client->team) {
			if (sv->teams[x].cur_clients ==
				sv->teams[x].max_clients)
				return -1;
			else
				return 0;
		}
	}
	return -1;
}

void exec_fork(server_t *sv, client_t *cl, char *input)
{
	if (!strcmp(input, "Fork")) {
		cl->cmd = 1;
		if (check_team(sv, cl) == -1) {
			cl->cmd = -1;
		} else {
			cl->action = get_time((double)42.00f / sv->freq);
			wait_timer(cl);
			dprintf(cl->sock, "ok\n");
		}
	}
}
