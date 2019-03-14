/*
** EPITECH PROJECT, 2018
** Zappy
** File description:
** Header
*/

#ifndef CLIENT_H
# define CLIENT_H

#include "inventory.h"
#include <sys/types.h>
#include <stdbool.h>

/// direction in which the player looks and moves.
typedef enum {
	FRONT,
	RIGHT,
	BACK,
	LEFT
}	direction_e;

/// How much cycles/time units a player can survive.
/// or MAX_HEALTH / frequency Seconds
# define HEALTH_PER_FOOD 126

/// Part 1 of the text that is received by the client when he types "inventory"
# define INV_FIRST "[ food %d, linemate %d, deraumere %d, sibur %d"

/// Part 2 of the text that is received by the client when he types "inventory"
# define INV_SEC ", mendiane %d, phiras %d, thystame %d ]\n"

/// Max Number of commands saved.
# define NB_COMMANDS 10

/// Structure used for a circular buffer implementation.
typedef struct	circ_s
{
	char	*(arr[NB_COMMANDS]);
}		circ_t;

/// Structure that contains client specific info,
/// there is one for every client.
typedef struct 		client_s
{
	int		cmd;
	double		action;
	double		 lifetime;
	int		dir;
	int		team;
	char 		*ip;
	int		x;
	int 		y;
	int		sock;
	int 		level;
	int 		health;
	int 		food;
	inventory_t	inv;
	circ_t		array;
	bool		graphical;
}			client_t;

void uplevel(client_t *);
void wait_timer(client_t *);
double get_time(double);
char *read_line(const int);
void put_in_buffer(circ_t *, char *);
void init_buffer(circ_t *);
int get_food(double);

#endif /* CLIENT_H */
