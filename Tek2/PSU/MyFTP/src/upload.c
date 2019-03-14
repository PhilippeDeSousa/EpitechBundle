/*
** EPITECH PROJECT, 2018
** FTP
** File description:
** create_server.c
*/

#include "my_ftp.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

static char *get_filename(t_client *client, char *path)
{
	char *filename = malloc(sizeof(char) * strlen(path) + 1);
	size_t i;
	size_t c;

	if (filename == NULL)
		return NULL;
	if (check_client(client) == -1)
		return NULL;
	for (i = 0; path[i] != ' ' && path[i]; i++);
	i += 1;
	for (c = 0; path[i] != '\0'; i++, c++)
		filename[c] = path[i];
	filename[c] = '\0';
	if (filename[0] == '\0') {
		xwrite(client->sock, "550 Please specifiy a file\n");
		return NULL;
	}
	return filename;
}

static int file_size(char *file)
{
	struct stat st;

	stat(file, &st);
	return st.st_size;
}

static char *new_fname(char *old)
{
	char *new = malloc(sizeof(char) * strlen(old) + 1);
	size_t c;
	size_t i;

	for (i = strlen(old); old[i] != '/'; i--);
	i++;
	for (c = 0; i < strlen(old); i++, c++)
		new[c] = old[i];
	new[c] = '\0';
	return new;
}

static void cat_file(t_client *client, int lsock, int fd, char *filename)
{
	int size = file_size(filename);
	char *buffer = malloc(sizeof(char) * size + 1);
	int newfile;

	filename = new_fname(filename);
	newfile = open(filename, O_CREAT | O_RDWR, 0644);
	xwrite(client->sock, "150 Opening ASCII mode data connection.\n");
	while (read(fd, buffer, size) > 0);
	buffer[size] = '\0';
	dprintf(newfile, "%s", buffer);
	xwrite(client->sock, "226 Transfer complete.\n");
	free(buffer);
	close(fd);
	close(lsock);
	close(newfile);
}

void upload(t_client *client, char *path)
{
	char *filename = get_filename(client, path);
	struct sockaddr_in addr;
	uint8_t dip[4] = {127, 0, 0, 1};
	socklen_t client_size = sizeof(addr);
	int lsock;
	int fd;

	if (filename == NULL)
		return;
	memcpy(&(addr.sin_addr), dip, 4);
	xwrite(client->sock, STOR_DIR);
	fd = open(filename, O_RDONLY);
	if (fd == -1) {
		xwrite(client->sock, "550 File does not exist\n");
		return;
	}
	lsock = accept_client(client->transfert.sock, addr, client_size);
	cat_file(client, lsock, fd, filename);
	xwrite(client->sock, DIR_OK);
	return;
}