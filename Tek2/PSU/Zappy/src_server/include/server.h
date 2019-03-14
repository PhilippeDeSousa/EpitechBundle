/*
** EPITECH PROJECT, 2018
** Zappy
** File description:
** Header
*/

#ifndef ZAPPY_H
# define ZAPPY_H

# include "usage.h"
# include "client.h"
# include "map.h"
# include <stdio.h>
# include <sys/socket.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <netdb.h>
# include <time.h>


/// Get a random material every time
# define RDMAT rand() % (E_COUNT + 7)

/// Seed used for random generation, change this to a fixed number
/// to get the same result every time.
# define SEED time(NULL)

/// Structure that contains team info, such as every members in the team
typedef struct 		team_s
{
	int		id;
	char		*name;
	int 		max_clients;
	int		cur_clients;
	client_t	*clients;
}			team_t;

/// Structure that contains server info
typedef struct	server_s
{
	int	port;
	int 	width;
	int 	height;
	int 	client_per_team;
	int 	nb_clients;
	int	nb_teams;
	int	sock;
	double	freq;
	size_t 	nb_actions;
	size_t 	nb_food;
	fd_set 	fd_serv;
	client_t **clients;
	map_t	**map;
	team_t	*teams;
}		server_t;

void server(server_t *);
void display_map(server_t *);
void my_getopt(int, char **, server_t *);
void xwrite(int, char *);
void create_server(server_t *);
void print_error(char *);
void create_client(server_t *server, fd_set, int);
void new_connection(server_t *server, int *sock);
void handle_sockets(server_t *server, fd_set *readfds, int *max_sock, int *i);
void free_tab(char **);
void make_connection(server_t *, client_t *);
void ignore(void);
void forward(server_t *, client_t *, char *);
void turn(server_t *, client_t *, char *);
void inventory(server_t *, client_t *, char *);
void init_mats(client_t *);
void set_mat(server_t *, int, int);
void connect_number(server_t *, client_t *, char *);
void close_server(server_t *);
void add_food(server_t *);
void exec_fork(server_t *, client_t *, char *);
void add_fd(client_t *, int *, int *, server_t *);
void rem_fd(client_t *, int *, int *, server_t *);
double get_time(double);

int isnum(char *);
int client_creater(server_t *, struct in_addr);

char **set_input(char *);
char *read_line(const int);

void elevation(client_t *, server_t *, char *);

void check_item_in_map(inventory_t inv, int fd);
void look(server_t *sv, client_t *client, char *input);
int get_real_pos(int pos, int max_pos);
void take_object(server_t *serv, client_t *cl, char *input);

void broadcast(server_t *sv, client_t *cl, char *input, int max_sock);
void graphic_client(server_t *, client_t *);
void send_map(server_t *, client_t *);

void eject(server_t *sv, client_t *cl, char *input, int max_sock);

#endif /* ZAPPY_H */
