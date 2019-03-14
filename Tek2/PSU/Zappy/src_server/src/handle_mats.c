/*
** EPITECH PROJECT, 2018
** cpp
** File description:
** cpp
*/

#include "server.h"
#include <time.h>
#include <sys/time.h>

/// Gets the current time.
/// @return Current time in microseconds
static suseconds_t rand_time(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_usec);
}

/// Sets the materials on a given tile.
/// @param server
/// @param posx
/// @param posy
void set_mat(server_t *server, int posx, int posy)
{
	srand(rand_time());
	for (int i = 0, mat_nb = RDMAT; i < rand() % 10; i++, mat_nb = RDMAT)
		switch (mat_nb) {
			case 0 ... 3 :
				server->map[posy][posx].inv.l += 1;
				break;
			case 4 ... 6 :
				server->map[posy][posx].inv.d += 1;
				break;
			case 7 ... 8 :
				server->map[posy][posx].inv.s += 1;
				break;
			case 9 ... 10 :
				server->map[posy][posx].inv.m += 1;
				break;
			case 11 :
				server->map[posy][posx].inv.p += 1;
				break;
			case 12 : server->map[posy][posx].inv.t += 1;
		}
}

void add_food(server_t *sv)
{
	static size_t old_act = 0;

	if (sv->nb_actions % 15 == 0 && sv->nb_actions != old_act) {
		sv->nb_food += 1;
		for (size_t i = 0; i < sv->nb_food; i++) {
			sv->map[rand()
				% sv->height][rand() % sv->width].inv.f += 1;
		}
	}
	old_act = sv->nb_actions;
}

/// Initializes to default values an inventory.
/// @param client
void init_mats(client_t *client)
{
	client->inv.players = 1;
	client->inv.l = 0;
	client->inv.d = 0;
	client->inv.s = 0;
	client->inv.m = 0;
	client->inv.p = 0;
	client->inv.t = 0;
	client->inv.f = 10;
}

/// Command that lists inventory
/// @param sv
/// @param client
/// @param input
void inventory(server_t *sv, client_t *client, char *input)
{
	if (strcmp(input, "Inventory") == 0) {
		client->cmd = 1;
		dprintf(client->sock, INV_FIRST, client->inv.f,
			client->inv.l, client->inv.d, client->inv.s);
		dprintf(client->sock, INV_SEC, client->inv.m,
			client->inv.p, client->inv.t);
		client->action = get_time((double)1.00f / sv->freq);
		wait_timer(client);
	}
}
