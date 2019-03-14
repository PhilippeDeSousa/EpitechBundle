/*
** EPITECH PROJECT, 2018
** FTP
** File description:
** create_server.c
*/

#include "my_ftp.h"
#include <string.h>

static char *get_file(char *path)
{
	char *file = malloc(sizeof(char) * strlen(path) + 1);
	size_t i;
	size_t c;

	for (i = 0; path[i] != ' ' &&
		path[i] != '\0' && path[i] != '\t';
		i++);
	i++;
	for (c = 0; path[i] != '\0' && i < strlen(path); i++, c++)
		file[c] = path[i];
	file[c] = '\0';
	return file;
}

void delete(t_client *client, char *path)
{
	char *file;

	if (client->log == false) {
		xwrite(client->sock, NOT_LOGGED);
		return;
	}
	file = get_file(path);
	if (file != NULL) {
		if (remove(file) == -1)
			xwrite(client->sock, PERM_DENIED);
		else
			xwrite(client->sock, FILE_ACTION_SUCCESS);
	}
	else
		xwrite(client->sock, PERM_DENIED);
	return;
}
