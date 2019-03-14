/*
** EPITECH PROJECT, 2018
** Zappy
** File description:
** main.c
*/

#include "server.h"

/// gets the team count
/// @param server
/// @param av
/// @param i

static void get_teams(server_t *server, char **av, int i)
{
	server->nb_teams = 0;
	for (int c = 0; av[i]; i++, c++) {
		if (av[i][0] != '-' && isnum(av[i]) == 0)
			server->nb_teams += 1;
	}
}

/// Initializes teams
/// @param sv
/// @param av
/// @param i
/// @return team

static team_t *set_teams(server_t *sv, char **av, int i)
{
	team_t *t;

	get_teams(sv, av, i);
	t = malloc(sizeof(team_t) * sv->nb_teams + 1);
	if (t == NULL)
		exit(84);
	for (int c = 0; av[i]; i++) {
		if (av[i][0] != '-' && isnum(av[i]) == 0) {
				t[c].name = strdup(av[i]);
				t[c].id = c + 1;
				t[c].max_clients = sv->client_per_team;
				t[c].cur_clients = 0;
				t[c].clients = malloc(sizeof(client_t) *
					sv->client_per_team + 1);
				c++;
			}
	}
	return t;
}

/// Verifies the validity of the arguments and initializes options.
/// @param ac
/// @param av
/// @param server
/// @return 1 if args are misused, 0 if OK

static int check_args(int ac, char **av, server_t *server)
{
	server->freq = 100;
	my_getopt(ac, av, server);
	for (int i = 0; i < ac; i++)
		if (strcmp(av[i], "-help") == 0)
			return 1;
		else if (strcmp(av[i], "-n") == 0)
			server->teams = set_teams(server, av, i + 1);
	if (!server->port || !server->width || !server->height
		|| !server->client_per_team || !server->teams)
			return 1;
	return 0;
}

/// Prints the usage
/// @param str
/// @return 84 (exit code)

static int usage(char *str)
{
	dprintf(2, "USAGE:\t%s%s%s\t%s\t%s\t%s\t%s\t%s\t%s%s", str, RET_USAGE1,
	RET_USAGE2, USAGE_PORT, USAGE_WIDTH, USAGE_HEIGHT, USAGE_NAME,
	USAGE_CLIENT, USAGE_FREQ, USAGE_FREQ1);
	return 84;
}

/// Entry point in C
/// @param ac (argument count)
/// @param av (argument values)
/// @return 84 if a fatal error occurs.

int main(int ac, char **av)
{
	server_t *sv = malloc(sizeof(server_t));

	if (sv == NULL)
		exit(84);
	if (check_args(ac, av, sv) != 0)
		return usage(av[0]);
	server(sv);
}
