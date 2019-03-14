/*
** check_commands.c for  in /home/WASSEX/Semestre1/PSU/PSU_2016_minishell1
** 
** Made by Wassim Alkayar
** Login   <WASSEX@epitech.net>
** 
** Started on  Tue Jun 13 15:57:34 2017 Wassim Alkayar
** Last update Sun Oct  8 02:07:41 2017 Wassim Alkayar
*/

#include "mysh.h"

int		check_env(t_dlist buffer_list)
{
  t_cell	*tmp;

  if (buffer_list->length != 1)
    return (0);
  tmp = buffer_list->begin;
  if ((my_strcmp(tmp->str, "env")) == 0 ||
      (my_strcmp(tmp->str, "setenv")) == 0)
    return (3);
  return (0);
}

int		check_setenv(t_dlist buffer_list, t_dlist envlist, int *retvalue)
{
  t_cell	*tmp;

  tmp = buffer_list->begin;
  if (buffer_list->length == 1 && (my_strcmp("setenv",
					     buffer_list->begin->str)) == 0)
    {
      env(envlist);
      return (0);
    }
  if ((my_strcmp(tmp->str, "setenv")) == 0)
    {
      if (buffer_list->length > 3)
	{
	  my_putstr(SETENV_ERR);
	  *retvalue = 1;
	}
      else
	return (4);
    }
  return (0);
}

int		check_unsetenv(t_dlist buffer_list, int *retvalue)
{
  t_cell	*tmp;

  tmp = buffer_list->begin;
  if ((my_strcmp(tmp->str, "unsetenv")) == 0)
    *retvalue = 1;
  if (buffer_list->length < 2 && (my_strcmp(tmp->str, "unsetenv")) == 0)
    {
      my_putstr(UNSETENV_ERR);
      return (0);
    }
  if ((my_strcmp(tmp->str, "unsetenv")) == 0)
    return (5);
  return (0);
}

int		check_right_redirections(t_dlist buffer_list)
{
  t_cell	*tmp;

  tmp = buffer_list->begin;
  while (tmp != NULL)
    {
      if ((my_strcmp(tmp->str, ">")) == 0 || (my_strcmp(tmp->str, ">>")) == 0)
	break ;
      tmp = tmp->next;
    }
  if (tmp == NULL || tmp->next == NULL)
    return (0);
  if ((my_strcmp(tmp->str, ">")) == 0)
    return (11);
  else if ((my_strcmp(tmp->str, ">>")) == 0)
    return (11);
  return (0);
}

int		check_left_redirections(t_dlist buffer_list)
{
  t_cell	*tmp;

  tmp = buffer_list->begin;
  while (tmp != NULL)
    {
      if ((my_strcmp(tmp->str, "<")) == 0 || (my_strcmp(tmp->str, "<<")) == 0)
	break ;
      tmp = tmp->next;
    }
  if (tmp == NULL || tmp->next == NULL)
    return (0);
  if ((my_strcmp(tmp->str, "<")) == 0)
    return (12);
  else if ((my_strcmp(tmp->str, "<<")) == 0)
    return (12);
  return (0);
}
