/*
** EPITECH PROJECT, 2018
** BSQ
** File description:
** main
*/

#include "my.h"
#include <stdlib.h>
#include <stdio.h>

static int check_pos(char **map, int y, int x)
{
	int nb_col;

	for (nb_col = 0; map[nb_col]; nb_col++);
	if (x >= my_strlen(map[0]) || x < 0)
		return -1;
	if (y >= nb_col || y < 0)
		return -1;
	return 0;
}

static int check_abs(char **map, int x, int y, int n)
{
	for (n = n; n > 0; n--) {
		if (check_pos(map, y, x - n) < 0 || map[y][x - n] != '.')
			return -1;
	}
	return 0;
}

static int check_ord(char **map, int x, int y, int n)
{
	int defsize = n;

	if (!map[y] || !map[y][x])
		return -1;
	for (n = n; n >= 0; n--) {
		if (check_pos(map, y - n, x) < 0 || map[y - n][x] != '.')
			return -1;
		else if (check_abs(map, x + defsize + 1, y - n, defsize) < 0)
			return -1;
	}
	return 0;
}

void check_square(char **map, t_square *cur)
{
	int size = 1;

	for (size = 1; check_ord(map, cur->x, cur->y + size, size) == 0; size++);
	cur->val = size;
}