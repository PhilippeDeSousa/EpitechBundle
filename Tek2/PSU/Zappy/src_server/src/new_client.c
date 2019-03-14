/*
** EPITECH PROJECT, 2018
** Zappy
** File description:
** create_server.c
*/

#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "server.h"

/// returns the ip address of the client
/// @param s (struct sockadrr * of the client)

static void *ipvx(struct sockaddr *s)
{
	if (s->sa_family == AF_INET)
		return &(((struct sockaddr_in *)s)->sin_addr);
	return &(((struct sockaddr_in6 *)s)->sin6_addr);
}

/// creates the structure of the client
/// @param server
/// @param client

static void init_struct(server_t *sv, client_t *client)
{
	int i;

	srand(SEED);
	client->x = rand() % sv->width;
	client->y = rand() % sv->height;
	for (i = 0; sv->map[client->y][client->x].val != '0' && i < 5; i++) {
		client->x = rand() % sv->width;
		client->y = rand() % sv->height;
	}
	client->dir = FRONT;
	client->food = 10;
	client->lifetime =
		get_time(HEALTH_PER_FOOD * client->food / sv->freq);
	client->level = 0;
	init_mats(client);
}

/// initializes the client
/// @param server
/// @param client
/// @param r

static void init_client(server_t *server, client_t *client,
			struct sockaddr_storage r)
{
	char ip[INET6_ADDRSTRLEN];

	client->ip = strdup(inet_ntop(r.ss_family, ipvx((struct sockaddr *)&r),
		ip, INET6_ADDRSTRLEN));
	init_struct(server, client);
	printf("New client from %s on pos: %d-%d\n", client->ip,
		client->x, client->y);
	dprintf(client->sock, "Welcome to zappy.\n");
	make_connection(server, client);
}

/// accepts a new connection
/// @param server
/// @param sock

void new_connection(server_t *server, int *sock)
{
	struct sockaddr_storage r;
	socklen_t len = sizeof(r);
	client_t *client = malloc(sizeof(client_t));

	if (client == NULL)
		perror("malloc");
	client->sock = accept(server->sock, (struct sockaddr *)&r, &len);
	if (client->sock == -1)
		perror("accept");
	FD_SET(client->sock, &server->fd_serv);
	if (client->sock > *sock)
		*sock = client->sock;
	if (server->clients[server->nb_clients - 1]) {
		dprintf(client->sock, "Too many people connected");
		close(client->sock);
	}
	else {
		init_client(server, client, r);
		server->clients[client->sock] = client;
	}
}
