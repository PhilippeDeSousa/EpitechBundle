/*
** EPITECH PROJECT, 2018
** FTP
** File description:
** print_error.c
*/

#include "my_ftp.h"
#include "help.h"
#include <stdio.h>
#include <string.h>

void xwrite(int sock, char *msg)
{
	if (write(sock, msg, strlen(msg)) == -1) {
		printf("%s\n", "Write error, closing the socket...");
		exit(0);
	}
}

int print_error(char *str)
{
	printf("%s\n", str);
	return 84;
}

void print_dir(t_client *client, char *message, char *directory)
{
	if (client->log == false) {
		xwrite(client->sock, NOT_LOGGED);
		return;
	}
	if (message != NULL)
		xwrite(client->sock, message);
	if (directory != NULL)
		xwrite(client->sock, directory);
	xwrite(client->sock, "\n");
}

void print_helper(t_client *client)
{
	if (client->log == false) {
		xwrite(client->sock, NOT_LOGGED);
		return;
	}
	xwrite(client->sock, HELPER_MESSAGE);
	xwrite(client->sock, USER);
	xwrite(client->sock, PASS);
	xwrite(client->sock, PWD);
	xwrite(client->sock, CDUP);
	xwrite(client->sock, QUIT);
	xwrite(client->sock, DELE);
	xwrite(client->sock, PWD);
	xwrite(client->sock, PASV);
	xwrite(client->sock, PORT);
	xwrite(client->sock, HELP);
	xwrite(client->sock, NOOP);
	xwrite(client->sock, RETR);
	xwrite(client->sock, STOR);
	xwrite(client->sock, LIST);
	xwrite(client->sock, "214 Help OK.\n");
}

void noop(t_client *client)
{
	if (client->log == false) {
		xwrite(client->sock, NOT_LOGGED);
		return;
	}
	dprintf(client->sock, COMMAND_CORRECT, "NOOP");
}
