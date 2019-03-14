/*
** EPITECH PROJECT, 2018
** Zappy
** File description:
** print_item
*/

#include "server.h"

/// sends the item string nb times to the fd
/// @param nb
/// @param str
/// @param fd
/// @return

int print_item(int nb, char *str, int fd)
{
	int i = 0;

	if (nb > 0) {
		while (i < nb) {
			dprintf(fd, "%s ", str);
			i++;
		}
		return 1;
	}
	return 0;
}

/// caps the position
/// @param pos
/// @param max_pos
/// @return pos € ]0:max_pos[

int get_real_pos(int pos, int max_pos)
{
	if (pos < 0)
		pos += max_pos;
	else
		pos %= max_pos;
	return pos;
}

/// sends inventory content to the fd
/// @param inv
/// @param fd

void check_item_in_map(inventory_t inv, int fd)
{
	print_item(inv.players, "player", fd);
	print_item(inv.l, "linemate", fd);
	print_item(inv.d, "deraumere", fd);
	print_item(inv.s, "sibur", fd);
	print_item(inv.m, "mendiane", fd);
	print_item(inv.p, "phiras", fd);
	print_item(inv.t, "thystame", fd);
	print_item(inv.f, "food", fd);
}
