/*
** cd_utils.c for  in /home/WASSEX/Semestre2/PSU/PSU_2016_minishell2/src
** 
** Made by Wassim Alkayar
** Login   <WASSEX@epitech.net>
** 
** Started on  Sat Aug 19 18:00:54 2017 Wassim Alkayar
** Last update Sat Aug 19 23:57:17 2017 Wassim Alkayar
*/

#include "mysh.h"

void		update_path(char *occ, t_dlist *envlist, char *new)
{
  t_cell	*tmp;

  tmp = (**envlist).begin;
  while (tmp != NULL)
    {
      if ((my_strcmp(occ, cut_str(tmp->str))) == 0)
	{
	  tmp->str = clear_buffer(tmp->str);
	  tmp->str = new;
	  return ;
	}
      tmp = tmp->next;
    }
}

char	*cut_path(char *path)
{
  int	i;
  int	j;
  char	*replace;

  i = 0;
  j = 0;
  if ((replace = malloc(sizeof(char) * (my_strlen(path) + 1))) == NULL)
    return (NULL);
  while (path[i] != '=')
    i += 1;
  i += 1;
  while (path[i] != '\0')
    {
      replace[j] = path[i];
      i += 1;
      j += 1;
    }
  replace[j] = '\0';
  return (replace);
}

char		*get_home_path(t_dlist *envlist)
{
  char		*replace;
  t_cell	*tmp;
  char		*tmpstr;

  tmp = (**envlist).begin;
  while (tmp != NULL)
    {
      tmpstr = my_strdup(tmp->str);
      if ((my_strcmp("HOME=", cut_str(tmpstr)) == 0))
	{
	  replace = cut_path(tmp->str);
	  free(tmpstr);
	  return (replace);
	}
      tmp = tmp->next;
    }
  return (NULL);
}
