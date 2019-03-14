/*
** left_redirections.c for  in /home/WASSEX/Semestre2/PSU/PSU_2016_minishell2/src
** 
** Made by Wassim Alkayar
** Login   <WASSEX@epitech.net>
** 
** Started on  Fri Aug 18 17:18:18 2017 Wassim Alkayar
** Last update Thu Sep 28 18:05:49 2017 Wassim Alkayar
*/

#include <fcntl.h>
#include <sys/wait.h>
#include "mysh.h"

static int	get_simple_or_double_redirection(t_dlist buffer_list)
{
  t_cell	*tmp;

  tmp = buffer_list->begin;
  while (tmp != NULL)
    {
      if ((my_strcmp(tmp->str, "<")) == 0)
	return (1);
      else if ((my_strcmp(tmp->str, "<<")) == 0)
	return (2);
      tmp = tmp->next;
    }
  return (0);
}

static t_dlist		get_new_list(t_dlist buffer_list, t_dlist new_list)
{
  t_cell		*tmp;
  char			*key;

  tmp = buffer_list->begin;
  key = my_strdup(((get_simple_or_double_redirection(buffer_list)) == 1) ?
		  "<" : "<<");
  while ((my_strcmp(tmp->str, key)) != 0)
    {
      new_list = push_back_dlist(new_list, tmp->str);
      tmp = tmp->next;
    }
  free(key);
  return (new_list);
}

char		*get_file_name(t_dlist buffer_list)
{
  t_cell	*tmp;

  tmp = buffer_list->begin;
  while (tmp->next != NULL)
    tmp = tmp->next;
  return (tmp->str);
}

int		left_redirections(t_dlist buffer_list,
				  t_dlist envlist,
				  int *retvalue)
{
  int		fd;
  pid_t		pid;
  int		status;
  t_dlist	new_list;

  new_list = NULL;
  if ((pid = fork()) == -1)
    exit(84);
  else if (pid == 0)
    {
      new_list = get_new_list(buffer_list, new_list);
      if ((fd = open(get_file_name(buffer_list), O_RDONLY)) == -1)
	exit(84);
      dup2(fd, 0);
      commands(new_list, envlist, retvalue);
      close(fd);
      new_list = free_list(new_list);
      exit(0);
    }
  else
    wait(&status);
  *retvalue = 0;
  return (0);
}
