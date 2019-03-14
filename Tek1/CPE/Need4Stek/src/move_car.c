/*
** move_car.c for n4s in /home/philippe/CPE/CPE_2016_n4s/tmp/Need4Stek-master
** 
** Made by Philippe De Sousa
** Login   <philippe.de-sousa-violante@epitech.eu>
** 
** Started on  Sat Oct 14 06:32:04 2017 Philippe De Sousa
** Last update Sun Oct 15 15:19:06 2017 Philippe De Sousa
*/

#include "n4s.h"

int	move_car()
{
  char	**tab;
  float mid;

  while (1)
    {
      if ((tab = exec_lidar()) == NULL)
	return (ERROR);
      if (!tab[15])
	return (ERROR);
      mid = atof(tab[15]);
      if (get_speed(mid) == 1)
	return (SUCCESS);
      if ((tab = exec_lidar()) == NULL)
	return (ERROR);
      mid = atof(tab[15]);
      if (get_dir(tab, mid) == 1)
	return (SUCCESS);
    }
  return (SUCCESS);
}
