/*
** EPITECH PROJECT, 2018
** Zappy
** File description:
** look.c
*/

#include "server.h"

/// sends front view to the client
/// @param map
/// @param client
/// @param wid
/// @param hei

void check_front(map_t **map, client_t *client, int wid, int hei)
{
	int i = 0;
	int x = 0;
	int y = -1;
	int tmp_y = 0;
	int tmp_x = 0;

	while (i <= client->level) {
		x = -(i + 1);
		while (x <= i + 1) {
			dprintf(client->sock, ",");
			tmp_x = get_real_pos(x + client->x, wid);
			tmp_y = get_real_pos(y + client->y, hei);
			check_item_in_map(map[tmp_y][tmp_x].inv
						, client->sock);
			x++;
		}
		y--;
		i++;
	}
	dprintf(client->sock, "]\n");
}

/// sends right view to the client
/// @param map
/// @param client
/// @param wid
/// @param hei

void check_right(map_t **map, client_t *client, int wid, int hei)
{
	int i = 0;
	int x = 1;
	int y = 0;
	int tmp_y = 0;
	int tmp_x = 0;

	while (i <= client->level) {
		y = -(i + 1);
		while (y <= i + 1) {
			dprintf(client->sock, ",");
			tmp_x = get_real_pos(x + client->x, wid);
			tmp_y = get_real_pos(y + client->y, hei);
			check_item_in_map(map[tmp_y][tmp_x].inv
						, client->sock);
			y++;
		}
		x++;
		i++;
	}
	dprintf(client->sock, "]\n");
}

/// sends back view to the client
/// @param map
/// @param client
/// @param wid
/// @param hei

void check_back(map_t **map, client_t *client, int wid, int hei)
{
	int i = 0;
	int x = 0;
	int y = 1;
	int tmp_y = 0;
	int tmp_x = 0;

	while (i <= client->level) {
		x = i + 1;
		while (x >= -(i + 1)) {
			dprintf(client->sock, ",");
			tmp_x = get_real_pos(x + client->x, wid);
			tmp_y = get_real_pos(y + client->y, hei);
			check_item_in_map(map[tmp_y][tmp_x].inv
						, client->sock);
			x--;
		}
		y++;
		i++;
	}
	dprintf(client->sock, "]\n");
}

/// sends left view to the client
/// @param map
/// @param client
/// @param wid
/// @param hei

void check_left(map_t **map, client_t *client, int wid, int hei)
{
	int i = 0;
	int x = -1;
	int y = 0;
	int tmp_y = 0;
	int tmp_x = 0;

	while (i <= client->level) {
		y = i + 1;
		while (y >= -(i + 1)) {
			dprintf(client->sock, ",");
			tmp_x = get_real_pos(x + client->x, wid);
			tmp_y = get_real_pos(y + client->y, hei);
			check_item_in_map(map[tmp_y][tmp_x].inv
						, client->sock);
			y--;
		}
		x--;
		i++;
	}
	dprintf(client->sock, "]\n");
}

/// sends the tiles seen by the client to the client,
/// depends on the client direction
/// @param sv
/// @param clt
/// @param input

void look(server_t *sv, client_t *clt, char *input)
{
	if (strcmp(input, "Look") == 0) {
		clt->cmd = 1;
		dprintf(clt->sock, "[");
		check_item_in_map(sv->map[clt->y][clt->x].inv, clt->sock);
		switch (clt->dir) {
		case (FRONT) :
			check_front(sv->map, clt, sv->width, sv->height);
			break;
		case (RIGHT) :
			check_right(sv->map, clt, sv->width, sv->height);
			break;
		case (BACK) :
			check_back(sv->map, clt, sv->width, sv->height);
			break;
		case (LEFT) :
			check_left(sv->map, clt, sv->width, sv->height);
			break;
		}
		clt->action = get_time((double)7.00f / sv->freq);
	}
}
