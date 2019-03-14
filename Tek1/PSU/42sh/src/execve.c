/*
** main.c for  in /home/WASSEX/Semestre1/PSU/PSU_2016_minishell1
** 
** Made by Wassim Alkayar
** Login   <WASSEX@epitech.net>
** 
** Started on  Mon Jun 12 15:22:27 2017 Wassim Alkayar
** Last update Sat Oct  7 14:44:06 2017 Wassim Alkayar
*/

#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include "mysh.h"

int		exec_all_path(t_dlist pathlist, char *binary, char**argv,
			      char **env)
{
  t_cell	*tmp;
  int		a;

  a = -1;
  tmp = pathlist->begin;
  while (tmp != NULL)
    {
      errno = 0;
      a = execve(link_strings(tmp->str, binary), argv, env);
      tmp = tmp->next;
    }
  if (a == -1)
    {
      my_putstr(binary);
      my_putstr((errno == ENOEXEC) ? BIN : CMD_NOT_FOUND);
      exit(1);
    }
  exit(0);
}

void		binary_exec(char *binary, char **argv, t_dlist envlist,
			    int *retvalue)

{
  pid_t		pid;
  int		status;
  char		**environment;
  t_dlist	pathlist;

  if (opendir(binary))
    {
      my_putstr(binary);
      my_putstr(NO_PERMISSION);
      *retvalue = 1;
      return ;
    }
  environment = list_to_tab(envlist);
  pathlist = get_all_path_bin(envlist);
  if ((pid = fork()) == -1)
    return ;
  else if (pid == 0)
    {
      if (execve(argv[0], argv, environment) == -1)
	exec_all_path(pathlist, binary, argv, environment);
    }
  else
    wait(&status);
  *retvalue = (WIFEXITED(status)) ? WEXITSTATUS(status) : print_errors(status);
}

void	help_get_apbt(char *new, char *tmpstr, int *i, int *j)
{
  new[*j] = tmpstr[*i];
  *i += 1;
  *j += 1;
}

void		get_all_path_bin_tool(int i, char *tmpstr,
				      t_dlist *pathlist, int a)
{
  int		j;
  char		*new;

  j = 0;
  if ((new = malloc(sizeof(char) * (my_strlen(tmpstr) + 1))) == NULL)
    return ;
  while (tmpstr != '\0')
    {
      help_get_apbt(new, tmpstr, &i, &j);
      if (tmpstr[i] == ':' || tmpstr[i] == '\0')
	{
	  if (tmpstr[i] == '\0')
	    a = 1;
	  i += 1;
	  new[j] = '/';
	  new[j + 1] = '\0';
	  *pathlist = push_back_dlist(*pathlist, new);
	  free(new);
	  if ((new = malloc(sizeof(char) * (my_strlen(tmpstr) + 1))) == NULL)
	    return ;
	  j = 0;
	  if (a == 1)
	    break ;
	}
    }
}

t_dlist		get_all_path_bin(t_dlist envlist)
{
  t_cell	*tmp;
  t_dlist	pathlist;
  int		i;
  int		a;

  pathlist = NULL;
  a = 0;
  i = 1;
  tmp = envlist->begin;
  while (tmp != NULL && ((my_strcmp(cut_str(tmp->str), "PATH=")) != 0))
    tmp = tmp->next;
  if (tmp == NULL)
    get_all_path_bin_tool(5, my_strcat(PATH, PATH_2), &pathlist, a);
  else
    {
      while (tmp != NULL && tmp->str[i - 1] != '=')
	i += 1;
      get_all_path_bin_tool(i, tmp->str, &pathlist, a);
    }
  return (pathlist);
}
