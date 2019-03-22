/*
** print_lemin.c for lemin in /home/philippe/CPE_2016_Lemin
** 
** Made by Philippe De Sousa
** Login   <philippe.de-sousa-violante@epitech.eu>
** 
** Started on  Thu Sep  7 11:37:28 2017 Philippe De Sousa
** Last update Sun Sep 24 00:05:22 2017 Philippe De Sousa
*/

#include "my.h"

int	nb_spaces(char *tmp)
{
  int	i;
  int	a;

  i = 0;
  a = 0;
  while (tmp[i])
    {
      if (tmp[i] == ' ')
	a++;
      i+=1;
    }
  return (a);
}

int	is_start(char *buff, int *start)
{
  if ((my_strcmp(buff, "##start")) == 1)
    {
      *start = 1;
      return (1);
    }
  else
    return (0);
}

int		is_tunnels(char *buff, int *tunnel)
{
  if (((nb_spaces(buff)) == 0) && (my_strcmp(buff, "##end") != 1))
    {
      *tunnel += 1;
      return (1);
    }
  return (0);
}

int		print_lemin(char **buff)
{
  int		i;
  t_print	print;

  init_val(&i, &print.room, &print.tunnel);
  if ((start_end(buff)) == -1)
    {
      my_putstr(TUNNELS);
      return (ERROR);
    }
  i = 1;
  while (buff[i])
    {
      if ((is_start(buff[i], &print.start)) == 1)
	my_putstr(START);
      else if ((is_tunnels(buff[i], &print.tunnel)) == 1 && print.tunnel == 1)
	  my_putstr(TUNNELS);
      if ((my_strcmp("##start", buff[i])) == 0)
	{
	  my_putstr(buff[i]);
	  my_putchar('\n');
	}
      i += 1;
    }
  return (SUCCESS);
}
