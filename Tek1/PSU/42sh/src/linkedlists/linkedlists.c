/*
** push_back_dlist.c for  in /home/WASSEX/jungle/pushswapessai/pushswap
** 
** Made by Wassim Alkayar
** Login   <WASSEX@epitech.net>
** 
** Started on  Tue Apr 11 18:16:33 2017 Wassim Alkayar
** Last update Mon Oct  2 23:54:12 2017 Wassim Alkayar
*/

#include "mysh.h"

t_dlist		push_back_dlist(t_dlist li, char *str)
{
  t_cell	*element;

  element = malloc(sizeof(*element));
  if (element == NULL)
    return (0);
  element->str = my_strdup(str);
  element->next = NULL;
  element->back = NULL;
  if (li == NULL)
    {
      li = malloc(sizeof(*li));
      if (li == NULL)
	return (0);
      li->length = 0;
      li->begin = element;
      li->end = element;
    }
  else
    {
      li->end->next = element;
      element->back = li->end;
      li->end = element;
    }
  li->length += 1;
  return (li);
}

t_dlist		create_env_dlist(t_dlist list, char **env, int isat)
{
  int		i;

  i = 1;
  if (isat == 1)
    {
      list = push_back_dlist(list, my_strcat(PATH, PATH_2));
      return (list);
    }
  else
    {
      while (env[i] != '\0')
	{
	  list = push_back_dlist(list, env[i]);
	  i += 1;
	}
      return (list);
    }
}

void		print_dlist(t_dlist list)
{
  t_cell	*tmp;

  if (list == NULL)
    return ;
  tmp = list->begin;
  while (tmp != NULL)
    {
      my_putstr(tmp->str);
      my_putchar('\n');
      tmp = tmp->next;
    }
}
