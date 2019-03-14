/*
** exit.c for  in /home/WASSEX/Semestre1/PSU/PSU_2016_minishell1
** 
** Made by Wassim Alkayar
** Login   <WASSEX@epitech.net>
** 
** Started on  Tue Jun 13 21:07:40 2017 Wassim Alkayar
** Last update Mon Sep  4 19:07:55 2017 Wassim Alkayar
*/

#include "mysh.h"

int	is_exit(t_dlist buffer_list, int *retvalue)
{
  *retvalue = check_exit(buffer_list, buffer_list->length);
  if (*retvalue == 1)
    {
      my_putstr(EXIT_ERR);
      return (0);
    }
  else if (*retvalue != 3 && *retvalue != -54)
    {
      my_putstr("exit\n");
      return (50);
    }
  return (0);
}

int	check_exit_value(char *str)
{
  int	i;

  i = 0;
  while (str[i] != '\0')
    {
      if (str[i] < '0' || str[i] > '9')
	return (2);
      i += 1;
    }
  return (1);
}

int		is_present_pipe(t_dlist buffer_list)
{
  t_cell	*tmp;
  int		i;

  i = 0;
  tmp = buffer_list->begin;
  while (tmp != NULL)
    {
      if ((my_strcmp(tmp->str, "|")) == 0)
	i += 1;
      tmp = tmp->next;
    }
  if (i > 0)
    return (1);
  return (0);
}

int		check_exit(t_dlist buffer_list, int list_length)
{
  t_cell	*tmp;

  tmp = buffer_list->begin;
  if ((my_strcmp(tmp->str, "exit") != 0) ||
      (is_present_pipe(buffer_list) != 0))
    return (-54);
  if (((list_length == 2) && ((my_strcmp(tmp->str, "exit")) == 0) &&
       ((check_exit_value(tmp->next->str) == 2)) &&
       ((is_present_pipe(buffer_list)) == 0)))
    return (1);
  if ((list_length == 2) && (my_strcmp(tmp->str, "exit")) == 0 &&
      (check_exit_value(tmp->next->str)) == 1)
    return (convertnb(tmp->next->str));
  return (0);
}
