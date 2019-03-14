/*
** EPITECH PROJECT, 2018
** BSQ
** File description:
** main
*/

#include "my.h"
#include <stdlib.h>
#include <stdio.h>

static void print_map(char **map)
{
	for (int y = 0; map[y]; y++) {
		my_putstr(1, map[y]);
		my_putstr(1, "\n");
	}
}

static void set_values(t_square *sq, int val, int x, int y)
{
	sq->val = val;
	sq->x = x;
	sq->y = y;
}

static void set_biggest_square(char **map, t_square *max)
{
	for (int y = max->y; y <= max->y + max->val - 1; y++)
		for (int x = max->x; x <= max->x + max->val - 1; x++)
			map[y][x] = 'X';
	print_map(map);
}

int bsq(char **map)
{
	t_square max;
	t_square cur;

	set_values(&max, 0, 0, 0);
	for (int y = 0; map[y]; y++)
		for (int x = 0; map[y][x]; x++) {
			if (map[y][x] == '.') {
				set_values(&cur, 0, x, y);
				check_square(map, &cur);
				if (max.val < cur.val)
					set_values(&max, cur.val, cur.x, cur.y);
			}
		}
	set_biggest_square(map, &max);
	for (int i = 0; map[i]; i++)
		free(map[i]);
	free(map);
	return 0;
}