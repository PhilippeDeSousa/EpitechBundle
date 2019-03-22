/*
** lemin.c for lemin in /home/maxence.fourrier/Documents/Project_C/CPE_2016_Lemin/src
** 
** Made by maxence.fourrier
** Login   <maxence.fourrier@epitech.eu>
** 
** Started on  Wed Sep  6 12:44:01 2017 maxence.fourrier
** Last update Mon Sep 25 18:29:59 2017 Wassim Alkayar
*/

#include "my.h"

int		nb_ants(char *buff)
{
  char	*str;
  int	i;

  i = 0;
  str = malloc(sizeof(char) * my_strlen(buff) + 1);
  while (buff[i] != '\n' && buff[i])
    {
      str[i] = buff[i];
      i += 1;
    }
  str[i] = '\0';
  return (my_str_to_int(str));
}

void		move_ants(t_dlist antlist, t_dlist pathlist)
{
  t_cell	*anttmp;
  t_cell	*pathtmp;

  anttmp = antlist->begin;
  pathtmp = pathlist->begin;
  while (anttmp != NULL)
    {
      while (pathtmp != NULL && (my_strcmp(pathtmp->a, anttmp->room)) == 0)
	pathtmp = pathtmp->next;
      if (pathtmp->next != NULL && (my_strcmp(pathtmp->next->b, "void")) == 1)
	{
	  my_putstr(my_strcat(my_strcat(my_strcat(anttmp->a,
						  anttmp->b), "-"), pathtmp->next->a));
	  my_putstr(" ");
	  anttmp->room = my_strdup(pathtmp->next->a);
	  if ((my_strcmp(pathtmp->next->a, pathlist->end->a)) == 0)
	    pathtmp->next->b = my_strdup("Empty");
	  pathtmp->b = my_strdup("void");
	  if ((my_strcmp(anttmp->room, pathlist->end->a)) == 1)
	    antlist->length -= 1;
	}
      pathtmp = pathlist->begin;
      anttmp = anttmp->next;
    }
}

void		begin_send_ants(t_dlist pathlist, int antsnb)
{
  t_dlist	antlist;
  t_cell	*tmp;
  int		i;

  i = 0;
  antlist = NULL;
  while (i++ < antsnb)
    antlist = push_back_dlist(antlist, "P", convertstr(i));
  tmp = antlist->begin;
  while (tmp != NULL)
    {
      tmp->room = my_strdup(pathlist->begin->a);
      tmp = tmp->next;
    }
  while (antlist->length != 0)
    {
      move_ants(antlist, pathlist);
      my_putstr("\n");
    }
}

int		lemin(char *buff)
{
  char		**entry;
  t_road	**road;
  t_room	**room;
  t_nb		nb;
  int		error;
  t_dlist	pathlist;

  error = 0;
  if (((entry = str_to_tab(buff)) == NULL) ||
      (number_of_ants(entry[0]) == ERROR) ||
      ((road = init_road(buff)) == NULL) || ((room = init_room(buff)) == NULL))
    error += 1;
  if ((print_lemin(entry) == ERROR) ||
      ((nb.beg = get_start(entry)) == NULL) ||
      ((nb.end = get_end(entry)) == NULL))
      error += 1;
  if (write(1, MOVES, 7) && error != 0)
    return (ERROR);
  if ((nb.nb_roads = get_road(nb.beg, nb.end, road)) == 0)
    return (ERROR);
  nb.nb_ants = nb_ants(buff);
  if ((pathlist = get_all_roads(road, nb.beg, nb.end)) == NULL)
    return (ERROR);
  begin_send_ants(pathlist, nb.nb_ants);
  return (SUCCESS);
}
