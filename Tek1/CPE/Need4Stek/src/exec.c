/*
** exec_cmd.c for n4s in /home/philippe/CPE/CPE_2016_n4s/tmp/Need4Stek-master
** 
** Made by Philippe De Sousa
** Login   <philippe.de-sousa-violante@epitech.eu>
** 
** Started on  Sat Oct 14 06:33:34 2017 Philippe De Sousa
** Last update Sun Oct 15 15:25:23 2017 Philippe De Sousa
*/

#include "n4s.h"

char	**exec_lidar()
{
  char	*str;

  my_putstr(1, LIDAR);
  if ((str = get_next_line(0)) == NULL)
    return (NULL);
  is_end(str);
  if ((str = rm_dots(str)) == NULL)
    return (NULL);
  return (str_to_tab(str));
}

int	exec(char *str)
{
  my_putstr(1, str);
  str = get_next_line(0);
  is_end(str);
  return (0);
}
