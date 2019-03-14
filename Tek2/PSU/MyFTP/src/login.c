/*
** EPITECH PROJECT, 2018
** FTP
** File description:
** create_server.c
*/

#include "my_ftp.h"
#include <string.h>

void login(t_client *client, char *command)
{
	char *usr = malloc(sizeof(char) * strlen(command) + 1);
	size_t i;
	size_t c;

	for (i = 0; i < strlen(command); i++)
		if (command[i] == ' ' || command[i] == '\t')
			break;
	i += 1;
	for (c = 0; i < strlen(command); i++, c++)
		usr[c] = command[i];
	usr[c] = '\0';
	xwrite(client->sock, LOGIN_SUCCESS);
	client->usr = true;
	client->name = usr;
}

int check_login(t_client *client)
{
	if (client->usr == false) {
		xwrite(client->sock, PASSW_ERROR);
		return -1;
	}
	for (size_t a = 0; a < strlen(LOGIN_CAP); a++) {
		if (client->name[a] != LOGIN_CAP[a]
			&& client->name[a] != LOGIN_LOW[a]) {
			xwrite(client->sock, LOGIN_ERROR);
			return -1;
		}
	}
	return 0;
}

void passw(t_client *client, char *command)
{
	char *usr = malloc(sizeof(char) * strlen(command) + 1);
	size_t i;
	size_t c;

	for (i = 0; i < strlen(command); i++)
		if (command[i] == ' ' || command[i] == '\t')
			break;
	i += 1;
	for (c = 0; i < strlen(command) - 1; i++, c++)
		usr[c] = command[i];
	usr[c] = '\0';
	if (check_login(client) == -1)
		return;
	else if (strlen(usr) == 0 && client->usr == true) {
		xwrite(client->sock, PASSW_SUCCESS);
		client->log = true;
	}
	else
		xwrite(client->sock, LOGIN_ERROR);
}
