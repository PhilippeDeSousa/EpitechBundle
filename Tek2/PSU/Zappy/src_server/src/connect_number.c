/*
** EPITECH PROJECT, 2018
** Zappy
** File description:
** create_server.c
*/

#include "server.h"


/// sends to the client the number of slots left
/// @param client
/// @param team
void print_number(client_t *client, team_t team)
{
	dprintf(client->sock, "%d\n", team.max_clients - team.cur_clients);
}


/// Prints to the the client socket,
/// the number of slots left on the team.
/// @param sv
/// @param client
/// @param input
void connect_number(server_t *sv, client_t *client, char *input)
{
	if (strcmp(input, "Connect_nbr") == 0) {
		client->cmd = 1;
		for (int x = 0; x < sv->nb_teams; x++) {
			if (client->team == sv->teams[x].id)
				print_number(client, sv->teams[x]);
		}
	}
}
