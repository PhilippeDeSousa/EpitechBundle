/*
** EPITECH PROJECT, 2018
** Zappy
** File description:
** main.c
*/

#include "server.h"
#include <signal.h>
#include <memory.h>

/// if this == true, we received a signal and it's time to exit

static bool sig_exit = false;

/// prints on stderr and exits
/// @param str

void print_error(char *str)
{
	write(2, str, strlen(str));
	exit(84);
}

/// sets the boolean sig_exit to true
/// @param sig

static void sig_handler(int sig)
{
	sig_exit = true;
	(void)sig;
}

/// select loop, stops when a SIGINT is received
/// @param server

static void handle_server(server_t *server)
{
	fd_set readfds;
	int max_sock = server->sock;
	struct sigaction sig_act = {0};
	struct timeval tv;

	tv.tv_sec = 20;
	tv.tv_usec = 0;
	FD_ZERO(&readfds);
	sig_act.sa_handler = sig_handler;
	sigaction(SIGINT, &sig_act, NULL);
	while (sig_exit == false) {
		readfds = server->fd_serv;
		if (select(max_sock + 1, &readfds, NULL, NULL, &tv) == -1) {
			if (sig_exit == true)
				return;
			print_error("Select error.");
		}
		for (int i = 0; i <= max_sock; i++)
			handle_sockets(server, &readfds, &max_sock, &i);
	}
}

/// this does everything server related,
/// it controls the creation and the cleanup of the server
/// @param server

void server(server_t *server)
{
	server->nb_clients = server->nb_teams * server->client_per_team + 4;
	create_server(server);
	server->nb_food = 5;
	server->nb_actions = 0;
	handle_server(server);
	close_server(server);
}
