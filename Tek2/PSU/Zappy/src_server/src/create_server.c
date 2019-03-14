/*
** EPITECH PROJECT, 2018
** Zappy
** File description:
** create_server.c
*/

#include "server.h"

/// Initializes inventory to default values.
/// @param sv
/// @param y
/// @param x
static void set_inventory(server_t *sv, int y, int x)
{
	sv->map[y][x].inv.players = 0;
	sv->map[y][x].inv.l = 0;
	sv->map[y][x].inv.d = 0;
	sv->map[y][x].inv.s = 0;
	sv->map[y][x].inv.m = 0;
	sv->map[y][x].inv.p = 0;
	sv->map[y][x].inv.t = 0;
	sv->map[y][x].inv.f = 5;
}

/// Allocates a map and initializes it to default values
/// @param sv
static void create_map(server_t *sv)
{
	int x;
	int y;

	sv->map = malloc(sizeof(map_t *) * sv->height + 8);
	if (sv->map == NULL)
		exit(84);
	for (y = 0; y < sv->height; y++) {
		sv->map[y] = malloc(sizeof(map_t) * sv->width + 9);
		if (sv->map[y] == NULL)
			exit(84);
		for (x = 0; x < sv->width; x++) {
			sv->map[y][x].val = '0';
			set_inventory(sv, y, x);
		}
		sv->map[y][x].val = '\0';
	}
	sv->map[y] = NULL;
	for (int y = 0; y < sv->height; y++)
		for (int x = 0; x < sv->width; x++)
		set_mat(sv, x, y);
}

/// Creates the master socket
/// @param port (specified in argv)
/// @return master socket
static int create_socket(int port)
{
	struct protoent *pe = getprotobyname("TCP");
	int sock = socket(AF_INET, SOCK_STREAM, pe->p_proto);
	int value = 1;
	struct sockaddr_in address;

	if (pe == 0)
		print_error("Prototype error");
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &value, sizeof(int));
	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	address.sin_addr.s_addr = INADDR_ANY;
	if (sock == -1 || bind(sock, (struct sockaddr *)&address,
		sizeof(address)) == -1 ||
		listen(sock, SOMAXCONN) == -1)
			print_error("Socket error");
	printf("Listening on port %d...\n", port);
	return sock;
}

/// Initializes the server's values + the master socket to the port.
/// @param server
void create_server(server_t *server)
{
	int sock = create_socket(server->port);

	server->clients = malloc(sizeof(client_t *) * server->nb_clients);
	for (int i = 0; i < server->nb_clients; i++)
		server->clients[i] = 0;
	server->sock = sock;
	FD_ZERO(&server->fd_serv);
	FD_SET(server->sock, &server->fd_serv);
	create_map(server);
}
