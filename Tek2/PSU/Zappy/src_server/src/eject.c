/*
** EPITECH PROJECT, 2018
** Zappy
** File description:
** eject.c
*/

#include <stdbool.h>
#include "server.h"

/// Eject command

void push_client(client_t *cl, int dir, int width, int height)
{
	switch (dir) {
	case FRONT:
		cl->y -= 1;
		if (cl->y < 0)
			cl->y += height;
		break;
	case RIGHT:
		cl->x = (cl->x + 1) % width;
		break;
	case BACK:
		cl->y = (cl->y + 1) % height;
		break;
	case LEFT:
		cl->x -= 1;
		if (cl->x < 0)
			cl->x += width;
		break;
	}
}

void send_answer(client_t *cl, bool ok, server_t *sv)
{
	if (ok)
		dprintf(cl->sock, "ok\n");
	else
		dprintf(cl->sock, "ko\n");
	cl->action = get_time((double)7.00f / sv->freq);
}

void eject(server_t *sv, client_t *cl, char *input, int max_sock)
{
	bool ok = false;

	if (strcmp(input, "Eject") == 0) {
		cl->cmd = 1;
		for (int i = 0; i < max_sock; i++) {
			if (sv->clients[i]
			&& i != cl->sock && sv->clients[i]->x == cl->x
			&& sv->clients[i]->y == cl->y) {
				push_client(sv->clients[i],
					cl->dir, sv->width, sv->height);
				dprintf(sv->clients[i]->sock,
					"eject: %i\n", cl->dir);
				ok = true;
			}
		}
		send_answer(cl, ok, sv);
	}
}
