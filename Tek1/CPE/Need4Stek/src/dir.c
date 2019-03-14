/*
** get_dir.c for n4s in /home/philippe/CPE/CPE_2016_n4s/tmp/Need4Stek-master
** 
** Made by Philippe De Sousa
** Login   <philippe.de-sousa-violante@epitech.eu>
** 
** Started on  Sat Oct 14 06:33:01 2017 Philippe De Sousa
** Last update Sun Oct 15 21:43:09 2017 Philippe De Sousa
*/

#include "n4s.h"

int	new_wheels(float i, char *new)
{
  my_putstr(1, WHEELS);
  if (i < 0.0)
    my_putchar(1, '-');
  my_putstr(1, new);
  if ((new = get_next_line(0)) == NULL)
    return (1);
  if (is_end(new) == 1)
    return (1);
  return (0);
}

int		get_dir(char **tab, float pos)
{
  float		right;
  float		left;
  int		i;

  left = atof(tab[1]);
  right = atof(tab[31]);
  if (pos >= 1600)
    i = new_wheels(WHEELS_TURN, "0.005\n");
  else if (pos >= 1100)
    i = new_wheels(WHEELS_TURN, "0.05\n");
  else if (pos >= 700)
    i = new_wheels(WHEELS_TURN, "0.1\n");
  else if (pos >= 500)
    i = new_wheels(WHEELS_TURN, "0.2\n");
  else if (pos >= 300)
    i = new_wheels(WHEELS_TURN, "0.3\n");
  else
    i = new_wheels(WHEELS_TURN, "0.5\n");
  return (i);
}
