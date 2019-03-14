/*
** EPITECH PROJECT, 2018
** Zappy
** File description:
** main.c
*/

#include "server.h"

static void free_map(server_t *sv)
{
	for (int y = sv->height; y >= 0; y--)
		free(sv->map[y]);
	free(sv->map);
}

static void free_clients(server_t *sv)
{
	for (int y = sv->nb_clients - 1; y >= 0; y--)
		free(sv->clients[y]);
	free(sv->clients);
}

static void free_teams(server_t *sv)
{
	for (int y = sv->nb_teams - 1; y >= 0; y--) {
		free(sv->teams[y].name);
		free(sv->teams[y].clients);
	}
	free(sv->teams);
}

/// Cleanup every allocated resources.
/// @param sv
void close_server(server_t *sv)
{
	printf("\nShutting down the server now...\n");
	close(sv->sock);
	free_map(sv);
	free_clients(sv);
	free_teams(sv);
	free(sv);
}
