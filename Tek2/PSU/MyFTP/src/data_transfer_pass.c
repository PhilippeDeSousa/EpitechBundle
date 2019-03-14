/*
** EPITECH PROJECT, 2018
** FTP
** File description:
** data_transfer.c
*/

#include "my_ftp.h"
#include <time.h>
#include <string.h>

static int get_ports(t_client *client)
{
	if (client->log == false) {
		xwrite(client->sock, NOT_LOGGED);
		return -1;
	}
	srand(time(NULL));
	client->transfert.fport = 255;
	client->transfert.sport = rand() % 256;
	client->transfert.port = client->transfert.fport * 256
				+ client->transfert.sport;
	dprintf(1, "Full port = %d\n", client->transfert.port);
	return 0;
}

static void display_passive(t_client *client)
{
	dprintf(client->sock, "%s(", PASV_MODE);
	for (size_t i = 0; i < strlen(client->ip); i++) {
		if (client->ip[i] == '.')
			dprintf(client->sock, "%c", 44);
		else
			dprintf(client->sock, "%c", client->ip[i]);
	}
	dprintf(client->sock, "%c%d%c%d)\n", 44, client->transfert.fport, 44,
		client->transfert.sport);
}

void transf_pass(t_client *client)
{
	struct sockaddr_in s_in;
	int sock;

	if (get_ports(client) == -1)
		return;
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1)
		return;
	s_in.sin_port = htons(client->transfert.port);
	s_in.sin_addr.s_addr = INADDR_ANY;
	s_in.sin_family = AF_INET;
	if (bind(sock, (struct sockaddr *)&s_in,
		sizeof(struct sockaddr_in)) == -1)
			return;
	if (listen(sock, CONNECT_NUMBER) == -1)
		return;
	client->transfert.sock = sock;
	display_passive(client);
	client->mode = PASSIVE;
}
