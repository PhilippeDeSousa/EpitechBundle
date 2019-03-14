/*
** EPITECH PROJECT, 2018
** FTP
** File description:
** list.c
*/

#include "my_ftp.h"
#include <sys/types.h>
#include <dirent.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

void list_dir(int sock, char *path)
{
	DIR *dir = opendir(path);
	struct dirent *file;

	if (dir == NULL) {
		xwrite(sock, "opendir error\n");
		exit(0);
	}
	while ((file = readdir(dir))) {
		if (file->d_name[0] != '.') {
			xwrite(sock, file->d_name);
			xwrite(sock, "\n");
		}
	}
	closedir(dir);
	return;
}

static void passive_list(t_client *client, char *path)
{
	int lsock;
	int Save;
	struct sockaddr_in addr;
	uint8_t dip[4] = {127, 0, 0, 1};
	socklen_t client_size = sizeof(addr);

	memcpy(&(addr.sin_addr), dip, 4);
	lsock = accept_client(client->transfert.sock, addr, client_size);
	xwrite(client->sock, LIST_DIR);
	if (strlen(path) == 0) {
		Save = dup(1);
		dup2(lsock, 1);
		system("ls -l");
		dup2(Save, 1);
	}
	else
		list_dir(lsock, path);
	xwrite(client->sock, DIR_OK);
	close(lsock);
}

int check_client(t_client *client)
{
	if (client->log == false) {
		xwrite(client->sock, NOT_LOGGED);
		return -1;
	}
	if (client->mode == 0) {
		xwrite(client->sock, LIST_ERROR);
		return -1;
	}
	return 0;
}

void list(t_client *client, char *command)
{
	char *path = malloc(sizeof(char) * strlen(command) + 1);
	size_t i;
	size_t c;

	if (check_client(client) == -1)
		return;
	for (i = 0; command[i] != ' ' &&
		command[i] != '\0' && command[i] != '\t';
		i++);
	i++;
	for (c = 0; command[i] != '\0' && i < strlen(command); i++, c++)
		path[c] = command[i];
	path[c] = '\0';
	if (client->mode == PASSIVE)
		passive_list(client, path);
	else
		passive_list(client, path);
}
