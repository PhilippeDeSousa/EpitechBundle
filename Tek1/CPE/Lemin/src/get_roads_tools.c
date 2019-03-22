/*
** get_roads_tools.c for  in /home/WASSEX/Semestre2/CPE/test/CPE_2016_Lemin
** 
** Made by Wassim Alkayar
** Login   <WASSEX@epitech.net>
** 
** Started on  Fri Sep 22 14:42:36 2017 Wassim Alkayar
** Last update Mon Sep 25 19:03:13 2017 Wassim Alkayar
*/

#include "my.h"

t_dlist		get_begin_roads(t_dlist roadlist, t_road **road, char *begin)
{
  int		i;

  i = 0;
  while (road[i])
    {
      if ((my_strcmp(road[i]->a, begin)) == 1)
	roadlist = push_back_dlist(roadlist, road[i]->a, road[i]->b);
      i += 1;
    }
  return (roadlist);
}

int		is_continue(char *room, t_road **road)
{
  int		i;

  i = 0;
  while (road[i])
    {
      if (road[i]-> a != NULL)
	{
	  if ((my_strcmp(road[i]->a, room)) == 1)
	    return (0);
	}
      i += 1;
    }
  return (1);
}

int		is_present_room(t_dlist pathlist, char *room)
{
  t_cell	*tmp;

  tmp = pathlist->begin;
  while (tmp != NULL)
    {
      if ((my_strcmp(tmp->a, room)) == 1)
	return (1);
      tmp = tmp->next;
    }
  return (0);
}

t_dlist		get_new_room(t_dlist pathlist, char *room, t_road **road)
{
  int		i;

  i = 0;
  while (road[i])
    {
      if ((my_strcmp(road[i]->a, room)) == 1 &&
	  is_present_room(pathlist, road[i]->b) == 0)
	{
	  pathlist = push_back_dlist(pathlist, road[i]->b, "void");
	  return (pathlist);
	}
      i += 1;
    }
  return (pathlist);
}
