/*
** push_back_dlist.c for  in /home/WASSEX/jungle/pushswapessai/pushswap
** 
** Made by Wassim Alkayar
** Login   <WASSEX@epitech.net>
** 
** Started on  Tue Apr 11 18:16:33 2017 Wassim Alkayar
** Last update Fri Sep 22 14:28:33 2017 Wassim Alkayar
*/

#include "my.h"

t_dlist		push_back_dlist(t_dlist li, char *str, char *str2)
{
  t_cell	*element;

  if ((element = malloc(sizeof(*element))) == NULL)
    return (NULL);
  element->a = my_strdup(str);
  element->b = my_strdup(str2);
  element->next = NULL;
  element->back = NULL;
  if (li == NULL)
    {
      if ((li = malloc(sizeof(*li))) == NULL)
	return (NULL);
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

void		print_dlist(t_dlist list)
{
  t_cell	*tmp;

  tmp = list->begin;
  while (tmp != NULL)
    {
      my_putstr(tmp->a);
      my_putstr(" - ");
      my_putstr(tmp->b);
      my_putstr("\n");
      tmp = tmp->next;
    }
}

t_dlist		free_list(t_dlist buffer_list, int list_length)
{
  t_cell	*tmp;
  t_cell	*del;
  t_dlist	replace;

  if (buffer_list == NULL)
    return (NULL);
  if (list_length == 0)
    return (0);
  replace = NULL;
  tmp = buffer_list->begin;
  while (tmp != NULL)
    {
      del = tmp;
      tmp = tmp->next;
      free(del);
      del = NULL;
    }
  return (replace);
}

t_dlist		list_to_list(t_dlist a, t_dlist b)
{
  t_cell	*tmp;

  tmp = a->begin;
  while (tmp != NULL)
    {
      b = push_back_dlist(b, tmp->a, tmp->b);
      tmp = tmp->next;
    }
  return (b);
}
