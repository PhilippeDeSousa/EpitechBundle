/*
** simple_pipe.c for  in /home/WASSEX/Semestre2/PSU/PSU_2016_42sh
** 
** Made by Wassim Alkayar
** Login   <WASSEX@epitech.net>
** 
** Started on  Fri Oct  6 22:53:10 2017 Wassim Alkayar
** Last update Sun Oct  8 15:21:49 2017 Wassim Alkayar
*/

#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include "mysh.h"

t_dlist		list_before_pipe(t_dlist buffer_list)
{
  t_dlist	new_list;
  static t_cell	*tmp;

  new_list = NULL;
  tmp = buffer_list->begin;
  while ((my_strcmp(tmp->str, "|")) != 0 && tmp != NULL)
    {
      new_list = push_back_dlist(new_list, tmp->str);
      tmp = tmp->next;
    }
  return (new_list);
}

t_dlist		list_after_pipe(t_dlist buffer_list)
{
  t_dlist	new_list;
  t_cell	*tmp;

  new_list = NULL;
  tmp = buffer_list->begin;
  while (tmp != NULL && (my_strcmp(tmp->str, "|")) != 0)
    tmp = tmp->next;
  tmp = tmp->next;
  while (tmp != NULL)
    {
      new_list = push_back_dlist(new_list, tmp->str);
      tmp = tmp->next;
    }
  return (new_list);
}

void		simple_pipe(t_dlist buffer_list,
			    t_dlist envlist,
			    int *retvalue)
{
  int		pfd[2];
  int		pid;

  if ((pipe(pfd)) == -1)
    return ;
  if ((pid = fork()) == -1)
    return ;
  if (pid == 0)
    {
      close(pfd[1]);
      dup2(pfd[0], 0);
      close(pfd[0]);
      commands(list_after_pipe(buffer_list), envlist, retvalue);
      exit(*retvalue);
    }
  else
    {
      close(pfd[0]);
      dup2(pfd[1], 1);
      close(pfd[1]);
      commands(list_before_pipe(buffer_list), envlist, retvalue);
      exit(*retvalue);
    }
}

void	prepare_simple_pipe(t_dlist buffer_list,
			    t_dlist envlist,
			    int *retvalue)
{
  int	stat;
  int	pid;

  if ((pid = fork()) == -1)
    return ;
  else if (pid == 0)
    simple_pipe(buffer_list, envlist, retvalue);
  else
    wait(&stat);
  *retvalue = (WIFEXITED(stat)) ? WEXITSTATUS(stat) : print_errors(stat);
}
