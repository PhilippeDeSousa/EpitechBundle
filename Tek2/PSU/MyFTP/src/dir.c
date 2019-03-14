/*
** EPITECH PROJECT, 2018
** FTP
** File description:
** create_server.c
*/

#include "my_ftp.h"
#include <string.h>

void cdup(t_client *client)
{
	char *parent = malloc(sizeof(char) * strlen(client->dir));
	size_t i;
	size_t c;

	for (i = strlen(client->dir); client->dir[i] != '/'; i--);
	for (c = 0; c < i; c++)
		parent[c] = client->dir[c];
	parent[c] = '\0';
	if (client->log == false)
		print_dir(client, NULL, NULL);
	else if (access(parent, F_OK | R_OK | W_OK) == -1)
		print_dir(client, "550 Can't access ", parent);
	else {
		chdir(parent);
		if (getcwd(client->dir, DIRECTORY_MAX_SIZE) == NULL) {
			xwrite(client->sock, "Getcwd error\n");
			exit(0);
		}
		print_dir(client, "250 Changing directory to ", client->dir);
	}
}

static char *set_new_path(t_client *client, char *new_path, char *path)
{
	size_t i;
	size_t c;

	for (i = 0; i < strlen(client->dir); i++)
		path[i] = client->dir[i];
	path[i] = '/';
	i++;
	for (c = 4; c < strlen(new_path); c++, i++)
		path[i] = new_path[c];
	path[i] = '\0';
	return path;
}

void cwd(t_client *client, char *new_path)
{
	char *path = malloc(sizeof(char) * strlen(new_path) +
			strlen(client->dir) + 3);

	if (strlen(new_path) == 3) {
		xwrite(client->sock, "550 Failed to change directory.\n");
		return;
	}
	path = set_new_path(client, new_path, path);
	if (access(path, F_OK | R_OK | W_OK) == -1)
		xwrite(client->sock, "550 Failed to change directory.\n");
	else {
		chdir(path);
		free(path);
		if (getcwd(client->dir, DIRECTORY_MAX_SIZE) == NULL) {
			xwrite(client->sock, "Getcwd error\n");
			exit(0);
		}
		print_dir(client, "250 Changing directory to ", client->dir);
	}
}

void set_root(t_client *client, char *path)
{
	if (access(path, F_OK | R_OK | W_OK) == -1) {
		xwrite(1, "Server's path is wrong.\n");
		exit(0);
	}
	chdir(path);
	if (getcwd(client->dir, DIRECTORY_MAX_SIZE) == NULL) {
		xwrite(client->sock, "Getcwd error\n");
		exit(0);
	}
}
