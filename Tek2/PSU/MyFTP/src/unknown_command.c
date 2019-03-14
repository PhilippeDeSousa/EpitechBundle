/*
** EPITECH PROJECT, 2018
** FTP
** File description:
** create_server.c
*/

#include "my_ftp.h"
#include <string.h>

void unknown_command(t_client *client, char *command)
{
	if (strcmp(command, "USER") != 0 &&
		strcmp(command, "PASS") != 0 &&
		strcmp(command, "CWD") != 0 &&
		strcmp(command, "CDUP") != 0 &&
		strcmp(command, "PWD") != 0 &&
		strcmp(command, "DELE") != 0 &&
		strcmp(command, "PASV") != 0 &&
		strcmp(command, "PORT") != 0 &&
		strcmp(command, "HELP") != 0 &&
		strcmp(command, "NOOP") != 0 &&
		strcmp(command, "RETR") != 0 &&
		strcmp(command, "STOR") != 0 &&
		strcmp(command, "LIST") != 0) {
		if (client->log == false) {
			xwrite(client->sock, NOT_LOGGED);
			return;
		}
		if (command[0] != '\0')
			xwrite(client->sock, UNKNOWN_COMMAND);
	}
}
