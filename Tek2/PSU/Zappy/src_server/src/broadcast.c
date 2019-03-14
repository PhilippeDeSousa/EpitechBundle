/*
** EPITECH PROJECT, 2018
** Zappy
** File description:
** Header
*/

#include "server.h"

/// Changes player direction and sends it
/// @param dest
/// @param dir
/// @param msg
/// @return new direction
int change_receiving_dir(client_t *dest, int dir, char *msg)
{
	if (dest->dir == RIGHT)
		dir = ((dir + 2) % 8) + 1;
	if (dest->dir == BACK)
		dir = ((dir + 4) % 8) + 1;
	if (dest->dir == LEFT)
		dir = ((dir + 6) % 8) + 1;
	dprintf(dest->sock, "message %i, %s\n", dir, msg);
	return dir;
}

///
/// @param x
/// @param y
/// @param dest
/// @param msg
/// @return
int check_direction(float x, float y, client_t *dest, char *msg)
{
	int dir = 0;

	(int)x == dest->x && (int)y == dest->y - 1 ? dir = 1 : ignore();
	(int)x == dest->x - 1 && (int)y == dest->y - 1 ? dir = 2 : ignore();
	(int)x == dest->x - 1 && (int)y == dest->y ? dir = 3 : ignore();
	(int)x == dest->x - 1 && (int)y == dest->y + 1 ? dir = 4 : ignore();
	(int)x == dest->x && (int)y == dest->y + 1 ? dir = 5 : ignore();
	(int)x == dest->x + 1 && (int)y == dest->y + 1 ? dir = 6 : ignore();
	(int)x == dest->x + 1 && (int)y == dest->y ? dir = 7 : ignore();
	(int)x == dest->x + 1 && (int)y == dest->y - 1 ? dir = 8 : ignore();
	if (dir)
		return change_receiving_dir(dest, dir, msg);
	return 0;
}

///
/// @param dest
/// @param source
/// @param msg
void trace_line(client_t *dest, client_t *source, char *msg)
{
	float destY = dest->y, destX = dest->x;
	float sourceY = source->y, sourceX = source->x;
	float x = 0, y = 0;
	float coef = (destY - sourceY) / (destX - sourceX);
	float b = destY - destX * coef;

	if (dest->x == source->x && dest->y == source->y)
		dprintf(dest->sock, "message 0, %s\n", msg);
	else {
		while ((int)(sourceX + x) != destX || (int)y != destY) {
			y = (sourceX + x) * coef + b;
			if (sourceX < destX)
				x += 0.1;
			else
				x -= 0.1;
			if (check_direction(sourceX + x, y, dest, msg))
				break;
		}
	}
}

/// Sends a message to everyone
/// @param sv
/// @param cl
/// @param input
/// @param max_sock
void broadcast(server_t *sv, client_t *cl, char *input, int max_sock)
{
	int i = 0;
	char *cmd, *msg; char *tmp;

	tmp = malloc(sizeof(char) * (strlen(input) + 1));
	if (tmp) {
		strcpy(tmp, input);
		cmd = strtok(tmp, " ");
		msg = strtok(NULL, " ");
		if (strcmp(cmd, "Broadcast") == 0) {
			cl->cmd = 1;
			while (i < max_sock) {
				if (sv->clients[i] && i != cl->sock)
					trace_line(sv->clients[i], cl, msg);
				i++;
			}
			dprintf(cl->sock, "ok\n");
			cl->action = get_time((double)7.00f / sv->freq);
		}
		free(tmp);
	}
}
