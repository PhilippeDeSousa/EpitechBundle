/*
** check_commands2.c for  in /home/WASSEX/Semestre2/PSU/PSU_2016_minishell2/src
** 
** Made by Wassim Alkayar
** Login   <WASSEX@epitech.net>
** 
** Started on  Sat Aug 19 16:49:26 2017 Wassim Alkayar
** Last update Sun Oct  8 12:32:12 2017 Wassim Alkayar
*/

#include "mysh.h"

int		check_cd(t_dlist buffer_list)
{
  t_cell	*tmp;

  if (buffer_list->length > 2)
    return (0);
  tmp = buffer_list->begin;
  if ((my_strcmp(tmp->str, "cd")) == 0 || ((my_strcmp(tmp->str, "..")) == 0))
    return (6);
  return (0);
}

void		disp_history(int ct, t_cell *tmp)
{
  int		div;
  int		mem;

  mem = ct;
  div = 100000;
  while (ct < div)
    {
      my_putstr(" ");
      ct = ct * 10;
    }
  my_put_nbr(mem);
  my_putstr("  ");
  my_putstr(tmp->time);
  my_putstr("  ");
  my_putstr(tmp->str);
  my_putchar('\n');
}

int		check_and_execute_history(t_shell *sh)
{
  int		ct;
  t_cell	*tmp;

  sh->retvalue = 0;
  ct = 1;
  if (sh->buffer_list->length > 1)
    return (0);
  if ((my_strcmp(sh->buffer_list->begin->str, "history")) == 0)
    {
      tmp = sh->history->begin;
      while (tmp != NULL)
	{
	  disp_history(ct, tmp);
	  tmp = tmp->next;
	  ct += 1;
	}
      return (1);
    }
  return (0);
}

int		check_globbing(t_shell *sh)
{
  t_cell	*tmp;
  int		i;

  if (sh->buffer_list->length <= 1)
    return (0);
  i = 0;
  tmp = sh->buffer_list->begin;
  while (tmp != NULL)
    {
      i = 0;
      while (tmp->str[i])
	{
	  if (tmp->str[i] == '*')
	    return (1);
	  i += 1;
	}
      tmp = tmp->next;
    }
  return (0);
}
