/*
** EPITECH PROJECT, 2018
** yes
** File description:
** a
*/

#include "my_ftp.h"
#include <string.h>

static char get_buff(const int fd)
{
	static char buff[1];
	static char *ptr;
	static int rd_val = 0;
	char c;

	if (rd_val == 0) {
		rd_val = read(fd, buff, 1);
		if (rd_val == 0)
			return (0);
		ptr = buff;
	}
	c = *ptr;
	ptr += 1;
	rd_val -= 1;
	return (c);
}

static int my_strlen(char *str)
{
	int i;

	for (i = 0; str[i]; i++);
	return i;
}

char *my_realloc(char *str)
{
	int size = my_strlen(str) + 2;
	char *ret = malloc(sizeof(char) * size);
	int i;

	if (ret == NULL)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		ret[i] = str[i];
	ret[i + 1] = '\0';
	free(str);
	return (ret);
}

char *read_line(const int fd)
{
	int i;
	char buff;
	char *line = malloc(sizeof(char) * 2);

	if (line == NULL)
		return (NULL);
	line[1] = '\0';
	buff = get_buff(fd);
	for (i = 0; buff && buff != '\n'; i++) {
		if (buff == '\0')
			return (NULL);
		line[i] = buff;
		line = my_realloc(line);
		buff = get_buff(fd);
	}
	line[i] = '\0';
	return (line);
}
