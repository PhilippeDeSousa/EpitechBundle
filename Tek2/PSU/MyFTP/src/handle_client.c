/*
** EPITECH PROJECT, 2018
** FTP
** File description:
** create_server.c
*/

#include "my_ftp.h"
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

static void init_client(t_client *client, int client_sock, struct in_addr in,
	char *path)
{
	client->sock = client_sock;
	client->dir = path;
	client->root = path;
	client->ip = inet_ntoa(in);
	client->mode = 0;
	client->usr = false;
	client->log = false;
	set_root(client, path);
	printf("New client logged in from %s.\n", client->ip);
	xwrite(client->sock, AUTH_SUCCESS);
	return;
}

static char *get_command(char *inc)
{
	char *command = malloc(sizeof(char) * strlen(inc) + 1);
	size_t i;

	for (i = 0; i < strlen(inc); i++) {
		if (inc[i] == ' ' && !inc[i + 1])
			break;
		if (inc[i] == ' ' && inc[i + 1] != ' ')
			break;
		if (inc[i] == '\t' || inc[i] == '\0' ||
		inc[i] == '\r')
			break;
		command[i] = inc[i];
	}
	command[i] = '\0';
	return command;
}

static void use_command(t_client *client, char *command, char *entry)
{
	strcmp(command, "USER") == 0 ? login(client, entry) : ignore();
	strcmp(command, "PASS") == 0 ? passw(client, entry) : ignore();
	strcmp(command, "CWD") == 0 ? cwd(client, entry) : ignore();
	strcmp(command, "CDUP") == 0 ? cdup(client) : ignore();
	strcmp(command, "PWD") == 0 ?
		print_dir(client, "257 ", client->dir) : ignore();
	strcmp(command, "DELE") == 0 ? delete(client, entry) : ignore();
	strcmp(command, "PASV") == 0 ? transf_pass(client) : ignore();
	strcmp(command, "PORT") == 0 ? transf_act(client, entry) : ignore();
	strcmp(command, "HELP") == 0 ? print_helper(client) : ignore();
	strcmp(command, "NOOP") == 0 ? noop(client) : ignore();
	strcmp(command, "RETR") == 0 ? download(client, entry) : ignore();
	strcmp(command, "STOR") == 0 ? upload(client, entry) : ignore();
	strcmp(command, "LIST") == 0 ? list(client, entry) : ignore();
	unknown_command(client, command);
}

static void new_client(int client_sock, struct in_addr in, char *path)
{
	t_client client;
	char *inc;
	char *command;

	init_client(&client, client_sock, in, path);
	while ((inc = read_line(client.sock))) {
		for (size_t i = 0; i < strlen(inc); i++)
			if (inc[i] == '\r')
				inc[i] = '\0';
		command = get_command(inc);
		if (strcmp(command, "QUIT") == 0)
			break;
		use_command(&client, command, inc);
		free(command);
		free(inc);
	}
	xwrite(client.sock, EXIT_MESSAGE);
	printf("Client disconnected from %s.\n", client.ip);
	close(client.sock);
	exit(0);
}

int client_creater(int client, struct in_addr in, char *path)
{
	int pid;

	if (client > 0) {
		pid = fork();
		if (pid == 0)
			new_client(client, in, path);
		else if (pid > 0)
			close(client);
		else
			return print_error("Fork failed");
	}
	return 0;
}
