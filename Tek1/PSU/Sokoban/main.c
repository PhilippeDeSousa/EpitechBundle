/*
** EPITECH PROJECT, 2018
** Sokoban
** File description:
** main
*/

#include "my.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

static void my_putstr(const int fd, const char *str)
{
    write(fd, str, my_strlen(str));
}

static int get_size(const char *filepath)
{
    FILE *file = fopen(filepath, "r");
    size_t len = 0;
    char *line = NULL;
    int i = 0;

    while (getline(&line, &len, file) > 0)
        i += my_strlen(line);
    free(line);
    fclose(file);
    return i;
}

t_map **set_map(const char *filepath)
{
    int size = get_size(filepath);
	int fd = open(filepath, O_RDONLY);
	char *buffer;
	t_map **map;

	if (fd == -1) {
		my_putstr(2, "Error: file does not exist\n");
		return NULL;
	}
	buffer = malloc(sizeof(char) * (size + 1));
	read(fd, buffer, size);
	buffer[size] = '\0';
	map = str_to_struct(buffer);
	free(buffer);
    close(fd);
	return map;
}

int main(const int ac, const char * const *av)
{
	t_map **map;

	if (ac != 2) {
		my_putstr(2, "Error: no file specified\n");
		return 84;
	}
	map = set_map(av[1]);
	if (map == NULL)
		return 84;
	return sokoban(map);
}
