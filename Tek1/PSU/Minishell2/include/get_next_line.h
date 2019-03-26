/*
** EPITECH PROJECT, 2018
** get_next_line par Philippe De Sousa
** File description:
** get_next_line.h
*/

#ifndef GET_NEXT_LINE_H_
# define GET_NEXT_LINE_H_

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# ifndef READ_SIZE
#  define READ_SIZE (42)
# endif /* !READ_SIZE */

char *get_next_line(const int fd);

#endif /* !GET_NEXT_LINE_H */
