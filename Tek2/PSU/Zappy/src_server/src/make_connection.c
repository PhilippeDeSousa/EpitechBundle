/*
** EPITECH PROJECT, 2018
** Zappy
** File description:
** create_server.c
*/

#include "server.h"

/// a condition failed so the client is disconnected
/// @param server
/// @param client

static void refuse_connection(server_t *server, client_t *client)
{
	printf("Client disconnected from %s.\n", client->ip);
	FD_CLR(client->sock, &server->fd_serv);
	server->map[client->y][client->x].val = '0';
	close(client->sock);
}

/// adds the client to the team
/// @param server
/// @param team
/// @param client

static void join_team(server_t *server, team_t *team, client_t *client)
{
	if (team->cur_clients == team->max_clients) {
		dprintf(client->sock, "ko Team %s is full\n", team->name);
		refuse_connection(server, client);
	} else {
		team->clients[team->cur_clients] = *client;
		team->cur_clients += 1;
		server->map[client->y][client->x].val = team->id + 48;
		client->team = team->id;
	}
	dprintf(client->sock, "%d\n", team->max_clients - team->cur_clients);
	dprintf(client->sock, "%d %d\n", server->width, server->height);
}

/// Connects a client to the server
/// and does the condition checks
/// @param server
/// @param client

void make_connection(server_t *server, client_t *client)
{
	char *inc;

	client->graphical = false;
	if ((inc = read_line(client->sock))) {
		if (!strcmp(inc, "GRAPHIC"))
			client->graphical = true;
		else {
			for (int x = 0; x < server->nb_teams; x++) {
				if (strcmp(server->teams[x].name, inc) == 0) {
					join_team(server,
						&server->teams[x], client);
					return;
				}
			}
			dprintf(client->sock,
				"ko Team %s does not exist.\n", inc);
			refuse_connection(server, client);
		}
	}
}
