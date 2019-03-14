/*
** change_directory.c for  in /home/WASSEX/Semestre1/PSU/PSU_2016_minishell1
** 
** Made by Wassim Alkayar
** Login   <WASSEX@epitech.net>
** 
** Started on  Tue Jun 13 18:17:44 2017 Wassim Alkayar
** Last update Sun Oct  8 01:30:55 2017 Wassim Alkayar
*/

#include <fcntl.h>
#include "mysh.h"

int		chdir_errors(char *path)
{
  int		cd_ret;
  int		open_ret;

  cd_ret = chdir(path);
  open_ret = open(path, O_RDONLY);
  if (open_ret == -1 && cd_ret == -1)
    {
      my_putstr(path);
      my_putstr(CD_ERR3);
      return (-1);
    }
  else if (cd_ret == -1 && open_ret != -1)
    {
      my_putstr(path);
      my_putstr(CD_ERR2);
      return (-1);
    }
  return (0);
}

int		use_chdir(char *path)
{
  char		pathmem[200];
  static char	*before;
  static char	*old1;
  static char	*old2;

  if ((my_strcmp(path, "-")) == 0)
    {
      if (old1 == NULL)
	{
	  my_putstr(UNFOUND_FILE);
	  return (-1);
	}
      path = my_strdup(((my_strcmp(old1, before)) == 0) ? old2 : old1);
    }
  if ((chdir_errors(path)) == -1)
    return (-1);
  old2 = my_strdup((old1 == NULL) ? getcwd(pathmem, sizeof(pathmem)) : old1);
  getcwd(pathmem, sizeof(pathmem));
  old1 = my_strdup(pathmem);
  before = my_strdup(pathmem);
  return (0);
}

char	*check_if(t_dlist buffer_list, t_dlist *envlist,
		  int list_length, char *path)
{
  if (list_length > 1)
    path = buffer_list->begin->next->str;
  else if ((my_strcmp("..", buffer_list->begin->str) == 0))
    path = my_strdup("..");
  else
    path = get_home_path(envlist);
  return (path);
}

void		change_directory(t_dlist buffer_list, t_dlist *envlist,
				 int list_length, int *retvalue)
{
  char		*path;
  char		pathmem[200];
  char		*beginpath;
  char		*finalpath;

  path = NULL;
  path = check_if(buffer_list, envlist, list_length, path);
  if ((use_chdir(path)) == -1)
    {
      *retvalue = 1;
      return ;
    }
  getcwd(pathmem, sizeof(pathmem));
  beginpath = my_strdup("PWD=");
  if (list_length == 1)
    {
      put_path_name(pathmem);
      finalpath = link_strings(beginpath, pathmem);
      update_path(beginpath, envlist, finalpath);
      return ;
    }
  put_path_name(pathmem);
  finalpath = link_strings(beginpath, pathmem);
  update_path(beginpath, envlist, finalpath);
}
