/*
** EPITECH PROJECT, 2018
** get_next_line
** File description:
** test_main: do not push!
*/

#include <stdio.h>
#include "get_next_line.h"

int main(void)
{
	char *buff;

	while ((buff = get_next_line(0)) != NULL) {
		printf("%s\n", buff);
		free(buff);
	}
	return 0;
}
