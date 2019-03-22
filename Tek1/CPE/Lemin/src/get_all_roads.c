/*
** get_all_roads.c for  in /home/WASSEX/Semestre2/CPE/CPE_2016_Lemin
** 
** Made by Wassim Alkayar
** Login   <WASSEX@epitech.net>
** 
** Started on  Wed Sep 20 14:04:56 2017 Wassim Alkayar
** Last update Mon Sep 25 19:02:48 2017 Wassim Alkayar
*/

#include "my.h"

int		is_continue_other(char *backroom, t_road **road)
{
  int		i;

  i = 0;
  while (road[i])
    {
      if ((my_strcmp(road[i]->a, backroom) == 1) ||
	  (my_strcmp(road[i]->b, backroom)) == 1)
	return (0);
      i += 1;
    }
  return (1);
}

t_road		**delete_bad_road(char *room, t_road **road)
{
  int		i;

  i = 0;
  while (road[i])
    {
      if ((my_strcmp(road[i]->a, room) == 1) ||
	  (my_strcmp(road[i]->b, room) == 1))
	road[i]->a = my_strdup("void");
      i += 1;
    }
  return (road);
}

t_dlist		find_good_path(char *a, char *b, t_road **road, char *end)
{
  t_dlist	pathlist;
  t_cell	*tmp;

  pathlist = NULL;
  pathlist = push_back_dlist(pathlist, a, "void");
  pathlist = push_back_dlist(pathlist, b, "void");
  tmp = pathlist->begin->next;
  while ((is_continue(tmp->a, road)) == 0)
    {
      pathlist = get_new_room(pathlist, tmp->a, road);
      if ((my_strcmp(pathlist->end->a, end)) == 1)
	return (pathlist);
      tmp = tmp->next;
      if ((is_continue(tmp->a, road)) != 0 &&
	  (is_continue_other(tmp->back->a, road)) == 0 &&
	  (pathlist->end->a != NULL) &&
	  (my_strcmp(pathlist->end->a, end)) == 0)
	{
	  delete_bad_road(tmp->a, road);
	  pathlist = NULL;
	  pathlist = push_back_dlist(pathlist, a, "void");
	  pathlist = push_back_dlist(pathlist, b, "void");
	  tmp = pathlist->begin->next;
	}
    }
  return (pathlist);
}

t_dlist		get_all_roads(t_road **road, char *begin, char *end)
{
  t_dlist	roadlist;
  t_dlist	pathlist;
  t_dlist	memlist;
  t_cell	*tmp2;

  road = epur_road(road);
  roadlist = NULL;
  memlist = NULL;
  roadlist = get_begin_roads(roadlist, road, begin);
  tmp2 = roadlist->begin;
  pathlist = find_good_path(tmp2->a, tmp2->b, road, end);
  memlist = list_to_list(pathlist, memlist);
  while (tmp2 != NULL)
    {
      pathlist = free_list(pathlist, pathlist->length);
      pathlist = find_good_path(tmp2->a, tmp2->b, road, end);
      if ((my_strcmp(pathlist->end->a, end)) == 1)
	return (pathlist);
      if (pathlist->length < memlist->length)
	{
	  memlist = free_list(memlist, memlist->length);
	  memlist = list_to_list(pathlist, memlist);
	}
      tmp2 = tmp2->next;
    }
  return ((my_strcmp(memlist->end->a, end)) == 1 ? memlist : NULL);
}
