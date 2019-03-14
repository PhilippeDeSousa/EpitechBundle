#ifndef MATCHSTICK_H
# define MATCHSTICK_H

#include <unistd.h>
#include <stdlib.h>

# define PLAYER 0
# define AI 1

void my_putstr(const int, const char*);
void display_map(char **);

int nb_matches(char **, int);
int my_strlen(const char *);
int get_nbr(const char *);
int matchstick(const int, const int);
int game_over(char **, int);

char *get_next_line(const int fd);

char **create_map(const int);
char **player_turn(char **, const int);
char **ai_turn(char **, const int);
char **remove_matches(char **, int, int, int);

#endif /* !MATCHSTICK_H */