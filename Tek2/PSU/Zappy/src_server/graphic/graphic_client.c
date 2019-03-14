/*
** EPITECH PROJECT, 2018
** Zappy
** File description:
** create_server.c
*/

#include "server.h"

void exit_graphical(client_t *client, server_t *server)
{
	printf("Graphical disconnected\n");
	FD_CLR(client->sock, &server->fd_serv);
	close(client->sock);
}

void graphic_client(server_t *sv, client_t *client)
{
	char *input;

	if ((input = read_line(client->sock))) {
		if (input[0] == '\0' ||
			input == NULL || strcmp(input, "QUIT") == 0)
			exit_graphical(client, sv);
		else if (strcmp(input, "get_map") == 0)
			send_map(sv, client);
	}
}
