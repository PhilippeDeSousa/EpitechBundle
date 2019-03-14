/*
** EPITECH PROJECT, 2018
** BSQ
** File description:
** main
*/

#include <unistd.h>
#include <stdlib.h>

int my_strlen(const char *str)
{
	int i;

	if (!str)
		return 0;
	for (i = 0; str[i]; i++);
	return i;
}

void my_putstr(int fd, const char *str)
{
	write(fd, str, my_strlen(str));
}

char **get_complete_tab(const char *map, char **tab)
{
	int	i = 0;
	int	j = 0;
	int	k = 0;

	while (map[i]) {
		j = 0;
		if ((tab[k] = malloc(sizeof(char) * my_strlen(map) + 1)) == NULL)
			return (NULL);
		while (map[i] && map[i] != '\n') {
			tab[k][j] = map[i];
			i += 1;
			j += 1;
		}
		tab[k][j] = '\0';
		k += 1;
		i += 1;
	}
	tab[k] = NULL;
	return (tab);
}

char **str_to_tab(const char *buffer)
{
	char **tab = malloc(sizeof(char *) * (my_strlen(buffer) + 1));

	if (tab == NULL)
		return (NULL);
	tab = get_complete_tab(buffer, tab);
	return (tab);
}