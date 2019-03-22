/*
** get_road.c for lemin in /home/philippe/CPE_2016_Lemin
** 
** Made by Philippe De Sousa
** Login   <philippe.de-sousa-violante@epitech.eu>
** 
** Started on  Fri Sep  8 13:58:23 2017 Philippe De Sousa
** Last update Wed Sep 20 14:19:07 2017 Wassim Alkayar
*/

#include "my.h"

int	get_road(char *begin, char *end, t_road **road)
{
  int	i;
  int	nb_beg;
  int	nb_end;

  i = 0;
  nb_beg = 0;
  nb_end = 0;
  while (road[i])
    {
      if ((my_strcmp(road[i]->a, begin)) == 1)
	nb_beg+=1;
      if ((my_strcmp(road[i]->b, end)) == 1)
	nb_end+=1;
      i+=1;
    }
  if (nb_beg >= nb_end)
    return (nb_end);
  else if (nb_end >= nb_beg)
    return (nb_beg);
  return (0);
}
