/*
** right_redirections.c for  in /home/WASSEX/Semestre2/PSU/PSU_2016_minishell2/src
** 
** Made by Wassim Alkayar
** Login   <WASSEX@epitech.net>
** 
** Started on  Thu Aug 17 18:18:05 2017 Wassim Alkayar
** Last update Thu Oct  5 16:00:20 2017 Wassim Alkayar
*/

#include <fcntl.h>
#include <sys/wait.h>
#include "mysh.h"

static int		get_simple_or_double_redirection(t_dlist buffer_list)
{
  t_cell		*tmp;

  tmp = buffer_list->begin;
  while (tmp != NULL)
    {
      if ((my_strcmp(tmp->str, ">")) == 0)
	return (1);
      else if ((my_strcmp(tmp->str, ">>")) == 0)
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
	       ">" : ">>");
  while ((my_strcmp(tmp->str, key)) != 0)
    {
      new_list = push_back_dlist(new_list, tmp->str);
      tmp = tmp->next;
    }
  free(key);
  return (new_list);
}

int		create_file(t_dlist buffer_list, int *fd)
{
  t_cell	*tmp;
  int		flags;

  flags = O_CREAT | O_RDWR;
  flags |= ((get_simple_or_double_redirection(buffer_list)) == 1)
    ? (O_TRUNC) : (O_APPEND);
  tmp = buffer_list->begin->next;
  if ((get_simple_or_double_redirection(buffer_list)) == 1)
    while ((my_strcmp(tmp->back->str, ">")) != 0)
      tmp = tmp->next;
  else if ((get_simple_or_double_redirection(buffer_list)) == 2)
    while ((my_strcmp(tmp->back->str, ">>") != 0))
      tmp = tmp->next;
  if ((*fd = (open(tmp->str, flags, 0644))) == - 1)
    {
      my_putstr("Couldn't create or open file.\n");
      return (84);
    }
  return (0);
}

int		right_redirections(t_dlist buffer_list,
				   t_dlist envlist,
				   int *retvalue)
{
  pid_t		pid;
  int		status;
  int		fd;
  t_dlist	new_list;

  new_list = NULL;
  if ((pid = fork()) == -1)
    exit(84);
  else if (pid == 0)
    {
      if ((create_file(buffer_list, &fd)) == 84)
	exit(84);
      new_list = get_new_list(buffer_list, new_list);
      dup2(fd, 1);
      commands(new_list, envlist, retvalue);
      close(fd);
      new_list = free_list(new_list);
      exit(*retvalue);
    }
  else
    wait(&status);
  *retvalue = WEXITSTATUS(status);
  return (0);
}
