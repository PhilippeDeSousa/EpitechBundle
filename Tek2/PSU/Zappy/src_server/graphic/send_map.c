/*
** EPITECH PROJECT, 2018
** Zappy
** File description:
** create_server.c
*/

#include "server.h"

void send_map(server_t *srv, client_t *cl)
{
	int x = 0;
	int y = 0;

	dprintf(cl->sock, "%i %i\n", srv->width, srv->height);
	while (x != srv->width || y != srv->height) {
		x = 0;
		while (x != srv->width) {
			dprintf(cl->sock, "%i ", srv->map[y][x].inv.f);
			dprintf(cl->sock, "%i ", srv->map[y][x].inv.l);
			dprintf(cl->sock, "%i ", srv->map[y][x].inv.d);
			dprintf(cl->sock, "%i ", srv->map[y][x].inv.s);
			dprintf(cl->sock, "%i ", srv->map[y][x].inv.m);
			dprintf(cl->sock, "%i ", srv->map[y][x].inv.p);
			dprintf(cl->sock, "%i ", srv->map[y][x].inv.t);
			dprintf(cl->sock, "%c\n", srv->map[y][x].val);
			x++;
		}
		y++;
	}

}
