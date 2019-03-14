/*
** test.c for test in /home/philippe
** 
** Made by Philippe De Sousa
** Login   <philippe.de-sousa-violante@epitech.eu>
** 
** Started on  Wed Oct  4 13:53:17 2017 Philippe De Sousa
** Last update Thu Oct  5 13:51:21 2017 Wassim Alkayar
*/

#include <stdio.h>
#include <string.h>
#include <glob.h>
#include "mysh.h"

char		**globbing(char *tok)
{
  glob_t	gl;

  glob(tok, GLOB_TILDE_CHECK, NULL, &gl);
  return (gl.gl_pathv);
}

int		check_star(char *str)
{
  int		i;

  i = 0;
  while (str[i])
    {
      if (str[i] == '*')
	return (1);
      i += 1;
    }
  return (0);
}

void		execute_globbing(t_shell *sh)
{
  t_cell	*tmp;
  char		*token;
  char		**tab;
  int		i;

  i = 0;
  tmp = sh->buffer_list->begin;
  while (tmp != NULL)
    {
      if ((check_star(tmp->str)) == 1)
	{
	  token = my_strdup(tmp->str);
	  tab = globbing(token);
	  tmp->str = my_strdup(tab[0]);
	  while (tab[++i])
	    sh->buffer_list = push_back_dlist(sh->buffer_list, tab[i]);
	  free(token);
	}
      tmp = tmp->next;
    }
  first_commands(sh);
}
