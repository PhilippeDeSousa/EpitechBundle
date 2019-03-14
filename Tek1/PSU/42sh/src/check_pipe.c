/*
** check_pipe.c for  in /home/WASSEX/Semestre2/PSU/PSU_2016_42sh
** 
** Made by Wassim Alkayar
** Login   <WASSEX@epitech.net>
** 
** Started on  Fri Oct  6 13:00:46 2017 Wassim Alkayar
** Last update Sun Oct  8 12:17:12 2017 Wassim Alkayar
*/

#include "mysh.h"

int		launch_pipe_fct(t_shell *sh)
{
  t_cell	*tmp;

  if ((my_strcmp(sh->buffer_list->begin->str, "|")) == 0)
    {
      my_putstr(INV_NULL);
      sh->retvalue = 1;
      return (1);
    }
  tmp = sh->buffer_list->begin;
  while (tmp != NULL)
    {
      if ((my_strcmp(tmp->str, "|")) == 0)
	{
	  if (tmp->next == NULL || (my_strcmp(tmp->next->str, "|")) == 0)
	    {
	      my_putstr(INV_NULL);
	      sh->retvalue = 1;
	      return (1);
	    }
	}
      tmp = tmp->next;
    }
  return (0);
}

int		check_pipe(t_shell *sh)
{
  int		i;
  int		a;
  t_cell	*tmp;

  i = 0;
  tmp = sh->buffer_list->begin;
  while (tmp != NULL)
    {
      if ((my_strcmp(tmp->str, "|")) == 0)
	i += 1;
      tmp = tmp->next;
    }
  if (i == 0)
    return (1);
  a = launch_pipe_fct(sh);
  if (a == 1)
    return (0);
  if (i == 1)
    prepare_simple_pipe(sh->buffer_list, sh->envlist, &sh->retvalue);
  else
    prepare_pipe(sh->buffer_list, sh->envlist, &sh->retvalue);
  return (0);
}
