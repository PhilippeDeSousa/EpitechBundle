/*
** setenv.c for  in /home/WASSEX/Semestre1/PSU/PSU_2016_minishell1
** 
** Made by Wassim Alkayar
** Login   <WASSEX@epitech.net>
** 
** Started on  Tue Jun 13 22:38:12 2017 Wassim Alkayar
** Last update Sun Oct  8 02:03:39 2017 Wassim Alkayar
*/

#include "mysh.h"

char	*cut_str(char *str)
{
  int	i;
  char	*replace;

  i = 0;
  replace = malloc(sizeof(char) * (my_strlen(str) + 1));
  if (replace == NULL)
    return (NULL);
  while (str[i] != '=')
    {
      replace[i] = str[i];
      i += 1;
    }
  replace[i] = '=';
  replace[i + 1] = '\0';
  return (replace);
}

int		check_duplicate(char *occ, t_dlist *envlist)
{
  t_cell	*tmp;

  occ = add_equal_sign(occ);
  tmp = (**envlist).begin;
  while (tmp != NULL)
    {
      if ((my_strcmp(occ, cut_str(tmp->str))) == 0)
	return (2);
      tmp = tmp->next;
    }
  return (0);
}

void		already_present_env(char *occ, t_dlist *envlist, char *new,
				    int list_length)
{
  t_cell	*tmp;
  char		*replace;

  occ = add_equal_sign(occ);
  tmp = (**envlist).begin;
  while (tmp != NULL)
    {
      if ((my_strcmp(occ, cut_str(tmp->str))) == 0)
	{
	  replace = my_strdup(tmp->str);
	  tmp->str = clear_buffer(tmp->str);
	  if (list_length == 2)
	    tmp->str = my_strdup(occ);
	  else
	    tmp->str = link_strings(cut_str(replace), new);
	}
      tmp = tmp->next;
    }
  free(occ);
  free(new);
}

void	my_setenv2(t_dlist *envlist, int list_length, char *str, char *str2)
{
  if (list_length == 2)
    {
      if ((check_duplicate(str, envlist)) == 2)
	already_present_env(str, envlist, str2, list_length);
      else
	*envlist = push_back_dlist(*envlist, add_equal_sign(str));
    }
  else if (list_length == 3)
    {
      if ((check_duplicate(str, envlist)) == 2)
	already_present_env(str, envlist, str2, list_length);
      else
	*envlist = push_back_dlist(*envlist, link_strings
				   (add_equal_sign(str), str2));
    }
}

void		my_setenv(t_dlist buffer_list,
			  t_dlist *envlist,
			  int list_length,
			  int *retvalue)
{
  t_cell	*tmp;
  char		*str;
  char		*str2;

  tmp = buffer_list->begin;
  str = tmp->next->str;
  str2 = NULL;
  *retvalue = 1;
  if (list_length >= 3)
    str2 = tmp->next->next->str;
  if (str[0] < '0' || (str[0] > '9' && str[0] < 'A') ||
      (str[0] > 'Z' && str[0] < 'a') || str[0] > 'z')
    my_putstr(SETENV_ERR_2);
  else if (str[0] >= '0' && str[0] <= '9')
    my_putstr(SETENV_ERR_2);
  else if ((check_non_alpha(str)) == 2)
    my_putstr(SE3);
  else
    {
      my_setenv2(envlist, list_length, str, str2);
      *retvalue = 0;
    }
}
