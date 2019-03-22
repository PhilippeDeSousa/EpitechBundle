/*
** ants.c for lemin in /home/philippe/CPE_2016_Lemin
** 
** Made by Philippe De Sousa
** Login   <philippe.de-sousa-violante@epitech.eu>
** 
** Started on  Thu Sep 21 16:17:21 2017 Philippe De Sousa
** Last update Sun Sep 24 17:23:30 2017 Philippe De Sousa
*/

#include "my.h"

int	all_num(char *buffer)
{
  int	i;

  i = 0;
  while (buffer[i])
    {
      if (buffer[i] < '0' || buffer[i] > '9')
	return (0);
      i += 1;
    }
  return (1);
}

int	start_end(char **buffer)
{
  int	i;

  i = 0;
  while ((my_strcmp(buffer[i], "##start") != 1))
    {
      i += 1;
      if (!buffer[i])
	return (-1);
    }
  i = 0;
  while ((my_strcmp(buffer[i], "##end") != 1))
    {
      i += 1;
      if (!buffer[i])
	return (-1);
    }
  return (SUCCESS);
}

int	number_of_ants(char *buffer)
{
  char	*tmp;
  int	i;

  i = 0;
  my_putstr(NOA);
  if ((tmp = malloc(sizeof(char) * my_strlen(buffer) + 1)) == NULL)
    return (ERROR);
  while (buffer[i] != '\n' && buffer[i])
    {
      tmp[i] = buffer[i];
      i += 1;
    }
  tmp[i] = '\0';
  if ((all_num(tmp)) == 0)
    {
      my_putstr(ROOMS);
      return (ERROR);
    }
  my_putstr(tmp);
  my_putchar('\n');
  my_putstr(ROOMS);
  return (SUCCESS);
}
