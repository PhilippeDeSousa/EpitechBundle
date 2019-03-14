/*
** EPITECH PROJECT, 2018
** Sokoban
** File description:
** Header
*/

#ifndef MY_H
#define MY_H

#include <ncurses.h>

#define WALL '#'
#define PLAYER 'P'
#define SPACE ' '
#define BOX 'X'
#define HOLE 'O'

typedef struct  s_player {
    int         x;
    int	        y;
}               t_player;

typedef struct	s_map {
    char        cur;
    char        old;
}               t_map;

void free_map(t_map **);
void print_map(t_map **);
int sokoban(t_map **);
int my_strlen(const char *);
t_map **str_to_struct(const char *);

#endif /*MY_H*/
