/*
** EPITECH PROJECT, 2018
** Zappy
** File description:
** Header
*/

#ifndef INVENTORY_H
# define INVENTORY_H

/// Structure that contains objects quantity,
/// there is one on every tile and one for every player.
typedef struct	inventory_s
{
	int	players;
	int	l;
	int	d;
	int	s;
	int	m;
	int	p;
	int	t;
	int	f;
}		inventory_t;

#endif /* INVENTORY_H */
