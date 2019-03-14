/*
** EPITECH PROJECT, 2018
** FTP
** File description:
** create_server.c
*/

#include "my_ftp.h"
#include <signal.h>
#include <netdb.h>
#include <memory.h>

static bool sig_exit = false;

static int create_socket(int port)
{
	struct sockaddr_in s_in;
	struct protoent *pe = getprotobyname("TCP");
	int sock;

	if (pe == 0)
		return print_error("Prototype error");
	sock = socket(AF_INET, SOCK_STREAM, pe->p_proto);
	if (sock == -1)
		return print_error("Couldn't open the socket");
	s_in.sin_port = htons(port);
	s_in.sin_addr.s_addr = INADDR_ANY;
	s_in.sin_family = AF_INET;
	if (bind(sock, (struct sockaddr *)&s_in,
		sizeof(struct sockaddr_in)) == -1)
			return print_error("Error while binding the socket");
	if (listen(sock, CONNECT_NUMBER) == -1)
		return print_error("Error while listening");
	printf("Listening on port %d...\n", port);
	return sock;
}

static void sig_handler(int sig)
{
	sig_exit = true;
	(void)sig;
}

static void accept_error(int client_sock, int sv_sock)
{
	close(client_sock);
	close(sv_sock);
	printf("Error when accepting the client, ");
	printf("server is now shutting down\n");
	exit(0);
}

int accept_client(int sv_sock, struct sockaddr_in addr,
	socklen_t client_size)
{
	int client_sock = accept(sv_sock, (struct sockaddr *)&addr,
			&client_size);
	if (client_sock == -1 && sig_exit == 0)
		accept_error(client_sock, sv_sock);
	return client_sock;
}

int create_server(int port, char *path)
{
	int client_sock;
	struct sigaction sig_act = {0};
	struct sockaddr_in addr;
	uint8_t dip[4] = {127, 0, 0, 1};
	socklen_t client_size = sizeof(addr);
	int sv_sock = create_socket(port);

	memcpy(&(addr.sin_addr), dip, 4);
	if (sv_sock == 84)
		return sv_sock;
	sig_act.sa_handler = sig_handler;
	sigaction(SIGINT, &sig_act, NULL);
	while (sig_exit == 0) {
		client_sock = accept_client(sv_sock, addr, client_size);
		if (client_creater(client_sock, addr.sin_addr, path) == 84)
			break;
	}
	printf("\nShutting down the server now...\n");
	close(sv_sock);
	return 0;
}
