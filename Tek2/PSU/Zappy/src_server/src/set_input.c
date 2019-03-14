/*
** EPITECH PROJECT, 2018
** Zappy
** File description:
** create_server.c
*/

#include "server.h"

///
/// @param inc
/// @return

char *remove_username(char *inc)
{
	char *ret = malloc(sizeof(char) * strlen(inc) + 2);
	size_t c = 0;

	if (ret == NULL)
		perror("Malloc");
	else {
		for (size_t i = 0; i < strlen(inc); i++, c++) {
			if (inc[i] == ':') {
				while (inc[i] != ' ')
					i++;
				i++;
			}
			ret[c] = inc[i];
		}
		ret[c] = '\0';
	}
	free(inc);
	return ret;
}

///
/// @param str
/// @return

char **set_input(char *str)
{
	char **tab = malloc(sizeof(char *) * strlen(str) + 15);
	int x;
	int y;
	int c = 0;

	if (tab == NULL || str[0] == 0)
		return NULL;
	for (y = 0; str[c]; y++, c++) {
		tab[y] = malloc(sizeof(char) * strlen(str) + 2);
		if (tab[y] == NULL)
			return NULL;
		for (x = 0; str[c] != ' ' && str[c] != '\0'
			&& str[c] != '\r' && str[c] != '\n'; c++, x++)
			tab[y][x] = str[c];
		tab[y][x] = '\0';
	}
	tab[y] = NULL;
	return tab;
}

/// frees a 2D char array
/// @param tab

void free_tab(char **tab)
{
	int x;

	if (tab == NULL)
		return;
	for (x = 0; tab[x]; x++);
	while (tab[x] != NULL) {
		free(tab[x]);
		x--;
	}
	free(tab);
}
