/*
** EPITECH PROJECT, 2018
** Zappy
** File description:
** handle_client.c
*/

#include "server.h"

/// Removes a client from its team.
/// @param client
/// @param server
static void leave_team(client_t *client, server_t *server)
{
	for (int x = 0; x < server->nb_teams; x++) {
		if (server->teams[x].id == client->team) {
			server->teams[x].cur_clients -= 1;
		}
	}
}

/// Disconnects the client and removes it from the map.
/// @param client
/// @param server
static void disconnect_client(client_t *client, server_t *server)
{
	printf("Client disconnected from %s.\n", client->ip);
	FD_CLR(client->sock, &server->fd_serv);
	server->map[client->y][client->x].val = '0';
	close(client->sock);
	if (client->ip)
		free(client->ip);
	leave_team(client, server);
}

/// Executes every commands possible in this game
/// (commands have an internal strcmp + custom checks)
/// @param serv
/// @param client
/// @param input (it's the command)
/// @param max_sock
static void execute_command(server_t *serv, client_t *client, char *input,
	int max_sock)
{
	forward(serv, client, input);
	turn(serv, client, input);
	inventory(serv, client, input);
	look(serv, client, input);
	broadcast(serv, client, input, max_sock);
	eject(serv, client, input, max_sock);
	connect_number(serv, client, input);
	take_object(serv, client, input);
	elevation(client, serv, input);
	exec_fork(serv, client, input);
	add_food(serv);
}

/// Read loop, gets the commands and executes the appropriate function.
/// @param client
/// @param serv
/// @param max_sock
static void read_client(client_t *client, server_t *serv, int max_sock)
{
	char *input;

	if ((input = read_line(client->sock))) {
		if (input[0] == '\0' ||	input == NULL
		|| strcmp(input, "QUIT") == 0
		|| client->lifetime < get_time(0.00f))
			disconnect_client(client, serv);
		else {
			client->cmd = -1;
			client->inv.f = get_food(client->lifetime);
			execute_command(serv, client, input, max_sock);
			if (client->cmd == -1)
				dprintf(client->sock, "ko\n");
			else
				serv->nb_actions += 1;
		}
		free(input);
	}
}

/// Uses the result from select to connect new clients,
/// or read the available commands from the client sockets.
/// @param server
/// @param readfds
/// @param max_sock
/// @param i
void handle_sockets(server_t *server, fd_set *readfds, int *ms, int *i)
{
	if (FD_ISSET(*i, readfds)) {
		if (*i == server->sock)
			new_connection(server, ms);
		else {
			if (server->clients[*i]->graphical == false &&
				server->clients[*i]->lifetime < get_time(0.00f))
				dprintf(server->clients[*i]->sock, "dead\n");
			if (server->clients[*i]->graphical == false)
				read_client(server->clients[*i], server, *ms);
			else
				graphic_client(server, server->clients[*i]);
		}
	}
}
