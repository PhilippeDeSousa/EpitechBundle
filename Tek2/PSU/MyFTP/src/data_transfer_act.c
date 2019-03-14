/*
** EPITECH PROJECT, 2018
** FTP
** File description:
** data_transfer.c
*/

#include "my_ftp.h"
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

static char *get_ip(char **tab)
{
	int size = strlen(tab[0]) + strlen(tab[1]) + strlen(tab[2])
	+ strlen(tab[3]);
	char *ip = malloc(sizeof(char) * size + 4);

	ip = tab[0];
	ip = strcat(ip, ".");
	for (int i = 1; i < 4; i++) {
		ip = strcat(ip, tab[i]);
		if (i != 3)
			ip = strcat(ip, ".");
	}
	ip[size + 3] = '\0';
	return ip;
}

static char **get_ports(char *entry)
{
	char **port_tab = malloc(sizeof(char *) * 7);
	size_t c = 5;
	size_t y;
	size_t x;

	for (y = 0; y < 6; y++) {
		port_tab[y] = malloc(sizeof(char) * strlen(entry) + 1);
		for (x = 0; entry[c] != 44 && entry[c]; x++, c++)
			port_tab[y][x] = entry[c];
		port_tab[y][x] = '\0';
		x = 0;
		c++;
	}
	port_tab[y] = NULL;
	return port_tab;
}

static char **create_ports(t_client *client, char *entry)
{
	char **port_tab = get_ports(entry);
	int i;

	if (client->log == false) {
		xwrite(client->sock, NOT_LOGGED);
		return NULL;
	}
	for (i = 0; port_tab[i] != NULL; i++);
	if (i != 6) {
		xwrite(client->sock, PORT_FORMAT);
		return NULL;
	}
	client->transfert.port = atoi(port_tab[4]) * 256 + (atoi(port_tab[5]));
	return port_tab;
}

static int act_connect(t_client *client, int sock, char *ip)
{
	struct sockaddr_in s_in;
	s_in.sin_family = AF_INET;
	s_in.sin_addr.s_addr = inet_addr(ip);
	s_in.sin_port = htons(client->transfert.port);
	if (connect(sock, (struct sockaddr *)&s_in, sizeof(s_in)) == -1) {
		dprintf(client->sock, PORT_ERROR);
		return -1;
	}
	return sock;
}

void transf_act(t_client *client, char *entry)
{
	char **port_tab = create_ports(client, entry);
	struct protoent *pe = getprotobyname("TCP");
	int sock;
	char *ip;

	if (port_tab == NULL)
		return;
	ip = get_ip(port_tab);
	pe = getprotobyname("TCP");
	sock = socket(AF_INET, SOCK_STREAM, pe->p_proto);
	if (sock == -1) {
		xwrite(client->sock, "Couldn't open the socket\n");
		return;
	}
	sock = act_connect(client, sock, ip);
	if (sock == -1)
		return;
	dprintf(client->sock, "I'm connected to %d\n", sock);
	client->transfert.sock = sock;
	client->mode = ACTIVE;
}
