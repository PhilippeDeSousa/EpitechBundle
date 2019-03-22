/*
** EPITECH PROJECT, 2018
** BSQ
** File description:
** main
*/

#include <unistd.h>
#include <stdlib.h>
#include "my.h"

int my_strlen(const char *str)
{
	int i;

	if (!str)
		return 0;
	for (i = 0; str[i]; i++);
	return i;
}

void print_map(t_map **map)
{
    char *line;
    int size;
    int x;
    int y;

    for (size = 0; map[0][size].cur; size++);
    line = malloc(sizeof(char) * (size + 1));
    for (y = 0; map[y]; y++) {
        for (x = 0; map[y][x].cur; x++)
            line[x] = map[y][x].cur;
        line[x] = '\0';
        mvprintw(y, 0, line);
    }
    refresh();
    free(line);
}

static t_map **get_complete_tab(const char *map, t_map **tab)
{
	int	i = 0;
	int	j = 0;
	int	k = 0;

	while (map[i]) {
		j = 0;
		if ((tab[k] = malloc(sizeof(t_map) * my_strlen(map) + 1)) == NULL)
			return (NULL);
		while (map[i] && map[i] != '\n') {
			tab[k][j].old = map[i];
            tab[k][j].cur = map[i];
			i += 1;
			j += 1;
		}
        tab[k][j].old = '\0';
        tab[k][j].cur = '\0';
		k += 1;
		i += 1;
	}
	tab[k] = NULL;
	return (tab);
}

t_map **str_to_struct(const char *buffer)
{
	t_map **map = malloc(sizeof(t_map *) * (my_strlen(buffer) + 1));

	if (map == NULL)
		return (NULL);
	map = get_complete_tab(buffer, map);
	return (map);
}

void free_map(t_map **tab)
{
    for (int i = 0; tab[i]; i++)
        free(tab[i]);
    free(tab);
}