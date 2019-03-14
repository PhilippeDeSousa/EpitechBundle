/*
** n4s.h for n4s in /home/philippe/CPE/CPE_2016_n4s
** 
** Made by Philippe De Sousa
** Login   <philippe.de-sousa-violante@epitech.eu>
** 
** Started on  Sat Oct 14 06:40:47 2017 Philippe De Sousa
** Last update Sun Oct 15 21:25:56 2017 Philippe De Sousa
*/

#ifndef N4S_H_
# define N4S_H_

/*		INCLUDES		*/

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include "get_next_line.h"

/*		DEFINES			*/

# define START "START_SIMULATION\n"
# define STOP "STOP_SIMULATION\n"
# define MAP_END "Track Cleared"
# define WHEELS "WHEELS_DIR:"
# define LIDAR "get_info_lidar\n"
# define SPEED_1_0 "CAR_FORWARD:1.0\n"
# define SPEED_0_8 "CAR_FORWARD:0.8\n"
# define SPEED_0_5 "CAR_FORWARD:0.5\n"
# define SPEED_0_4 "CAR_FORWARD:0.4\n"
# define SPEED_0_2 "CAR_FORWARD:0.2\n"
# define SPEED_0_1 "CAR_FORWARD:0.1\n"
# define WHEELS_TURN left - right
# define SUCCESS (0)
# define ERROR (1)

/*		BASICS			*/

void		my_putchar(int, char);
void		my_putstr(int, char*);
int		my_strlen(char *);
int		my_strcmp(char *, char *);
char		*get_next_line(const int);
char		**str_to_tab(char*);

/*		SRCS			*/

int		get_dir(char **, float);
int		exec(char *);
int		move_car(void);
int		is_end(char *);
int		get_speed(float);
char		*rm_dots(char *);
char		**exec_lidar(void);
float		my_atof(char *);

#endif	/* !N4S_H_ */
