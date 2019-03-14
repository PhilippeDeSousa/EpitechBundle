/*
** detect_end.c for n4s in /home/philippe/CPE/CPE_2016_n4s/tmp/Need4Stek-master
** 
** Made by Philippe De Sousa
** Login   <philippe.de-sousa-violante@epitech.eu>
** 
** Started on  Sat Oct 14 06:33:19 2017 Philippe De Sousa
** Last update Sun Oct 15 21:35:54 2017 Philippe De Sousa
*/

#include "n4s.h"

void	end(char *str)
{
  if (str)
    free(str);
  exec(STOP);
  exit(SUCCESS);
}

int	is_end(char *str)
{
  int	i;
  int	c;
  char	*new;

  if ((new = malloc(sizeof(char *) * my_strlen(str))) == NULL)
    end(NULL);
  i = my_strlen(str) - 1;
  while (str[i] != ':' && str[i])
    i -= 1;
  i -= 1;
  while (str[i] != ':' && str[i])
    i -= 1;
  i += 1;
  c = 0;
  while (str[i] != ':' && str[i])
    new[c++] = str[i++];
  new[c] = 0;
  if (strcmp(MAP_END, new) == 0)
    end(new);
  free(new);
  return (0);
}
