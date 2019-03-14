/*
** simple_pipe.c for  in /home/WASSEX/Semestre2/PSU/PSU_2016_minishell2
** 
** Made by Wassim Alkayar
** Login   <WASSEX@epitech.net>
** 
** Started on  Sun Sep  3 22:57:21 2017 Wassim Alkayar
** Last update Sun Oct  8 15:21:33 2017 Wassim Alkayar
*/

#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include "mysh.h"

t_dlist		get_next_command_pipe(t_cell **tmp)
{
  t_dlist	tmplist;

  tmplist = NULL;
  while (*tmp != NULL)
    {
      if ((my_strcmp((**tmp).str, "|")) == 0)
	{
	  if ((**tmp).next != NULL)
	    *tmp = (**tmp).next;
	  break ;
	}
      tmplist = push_back_dlist(tmplist, (**tmp).str);
      *tmp = (**tmp).next;
    }
  return (tmplist);
}

void		my_dup(int *fd, t_cell *tmp, int p[2])
{
  dup2(*fd, 0);
  if (tmp != NULL)
    dup2(p[1], 1);
  close(p[0]);
}

void		parent_tour(int stat, int p[2], int *fd, int *retvalue)
{
  close(p[1]);
  *fd = p[0];
  *retvalue = (WIFEXITED(stat)) ? WEXITSTATUS(stat) : print_errors(stat);
}

int		my_pipe(t_dlist buffer_list,
			t_dlist envlist,
			int *retvalue,
			int stat)
{
  t_dlist	tmplist;
  t_cell	*tmp;
  int		p[2];
  int		pid;
  int		fd;

  fd = 0;
  tmp = buffer_list->begin;
  while (tmp != NULL)
    {
      tmplist = get_next_command_pipe(&tmp);
      pipe(p);
      pid = fork();
      if (pid == 0)
	{
	  my_dup(&fd, tmp, p);
	  commands(tmplist, envlist, retvalue);
	  exit(*retvalue);
	}
      else
	parent_tour(stat, p, &fd, retvalue);
    }
  wait(&stat);
  return (*retvalue);
}

void	prepare_pipe(t_dlist buffer_list,
		     t_dlist envlist,
		     int *retvalue)
{
  int	stat;

  stat = 0;
  *retvalue = my_pipe(buffer_list, envlist, retvalue, stat);
}
