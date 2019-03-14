/*
** EPITECH PROJECT, 2018
** cpp
** File description:
** cpp
*/

#include "server.h"
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

/// Checks if the string is a positive number.
/// @param num
/// @return number a positive number, false if negative or not a number
int isnum(char *num)
{
	char *ptr = num;

	while (*ptr) {
		if (!isdigit(*ptr))
			return 0;
		++ptr;
	}
	return atoi(num);
}

/// Switch Case for the getopt flags
/// @param c
/// @param sv
static void sw_cs(int c, server_t *sv)
{
	switch (c) {
		case 'p':
			sv->port = isnum(optarg);
			break;
		case 'x':
			sv->width = isnum(optarg);
			break;
		case 'y':
			sv->height = isnum(optarg);
			break;
		case 'c':
			sv->client_per_team = isnum(optarg);
			break;
		case 'f':
			sv->freq = isnum(optarg);
			break;
	}
}

/// Initializes the program options with the flags set in argv.
/// @param argc
/// @param argv
/// @param sv
void my_getopt(int argc, char **argv, server_t *sv)
{
	int c;

	while (1)
	{
		static struct option long_options[] =
			{
				{"port", required_argument, 0, 'p'},
				{"width", required_argument, 0, 'x'},
				{"height", required_argument, 0, 'y'},
				{"clientsNB", required_argument, 0, 'c'},
				{"freq", required_argument, 0, 'f'},
				{"names", required_argument, 0, 'f'},
				{0, 0, 0, 0}
			};
		int option_index = 0;
		c = getopt_long (argc, argv, "p:x:y:c:d:f:n:",
			long_options, &option_index);
		if (c == -1)
			break;
		sw_cs(c, sv);
	}
}
