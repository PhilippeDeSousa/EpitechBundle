/*
** EPITECH PROJECT, 2018
** BSQ
** File description:
** main
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "my.h"

#include <stdlib.h>
#include <unistd.h>

int get_size(const char *file)
{
	struct stat st;

	stat(file, &st);
	return st.st_size;
}

char **set_map(const char *filepath)
{
	int fd = open(filepath, O_RDONLY);
	char *buffer;
	char **map;

	if (fd == -1) {
		my_putstr(2, "Error: file does not exist\n");
		return NULL;
	}
	buffer = malloc(sizeof(char) * (get_size(filepath) + 1));
	while (read(fd, buffer, get_size(filepath)) > 0);
	buffer[get_size(filepath)] = '\0';
	map = str_to_tab(buffer);
	free(buffer);
	return map;
}

int main(const int ac, const char * const *av)
{
	char **map;

	if (ac != 2) {
		my_putstr(2, "Error: no file specified\n");
		return 84;
	}
	map = set_map(av[1]);
	if (map == NULL)
		return 84;
	return bsq(map);
}
