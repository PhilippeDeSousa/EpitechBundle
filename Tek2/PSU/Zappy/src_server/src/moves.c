/*
** EPITECH PROJECT, 2018
** Zappy
** File description:
** handle_client.c
*/

#include "server.h"

/// moves the client
/// @param srv
/// @param cl
/// @param x
/// @param y

void move(server_t *srv, client_t *cl, int x, int y)
{
	if (x == srv->width)
		x = 0;
	else if (x == -1)
		x = srv->width - 1;
	cl->x = x;
	if (y == srv->height)
		y = 0;
	else if (y == -1)
		y = srv->height - 1;
	cl->y = y;
	cl->cmd = 1;
}

/// makes the client go forward (depends on the direction the client is facing)
/// @param srv
/// @param cl
/// @param inp

void move_dir(server_t *srv, client_t *cl)
{
	cl->dir == FRONT ?
		move(srv, cl, cl->x, cl->y - 1) : ignore();
	cl->dir == RIGHT ?
		move(srv, cl, cl->x + 1, cl->y) : ignore();
	cl->dir == BACK ?
		move(srv, cl, cl->x, cl->y + 1) : ignore();
	cl->dir == LEFT ?
		move(srv, cl, cl->x - 1, cl->y) : ignore();
}

void forward(server_t *srv, client_t *cl, char *inp)
{
	if (strcmp(inp, "Forward") == 0) {
		if (srv->map[cl->y][cl->x].inv.players > 0)
			srv->map[cl->y][cl->x].inv.players--;
		srv->map[cl->y][cl->x].val = '0';
		move_dir(srv, cl);
		if (cl->cmd == -1) {
			srv->map[cl->y][cl->x].val = cl->team + 48;
			return;
		}
		srv->map[cl->y][cl->x].inv.players++;
		srv->map[cl->y][cl->x].val = cl->team + 48;
		cl->action = get_time((double)7.00f / srv->freq);
		wait_timer(cl);
		dprintf(cl->sock, "ok\n");
	}
}

/// changes the direction of the client
/// @param srv
/// @param cl
/// @param inp

void turn(server_t *srv, client_t *cl, char *inp)
{
	if (strcmp(inp, "Right") == 0) {
		if (cl->dir == LEFT)
			cl->dir = FRONT;
		else
			cl->dir += 1;
	} else if (strcmp(inp, "Left") == 0) {
		if (cl->dir == FRONT)
			cl->dir = LEFT;
		else
			cl->dir -= 1;
	} else
		return;
	cl->cmd = 1;
	cl->action = get_time((double)7.00f / srv->freq);
	dprintf(cl->sock, "ok\n");
}
