/*
** epur_road.c for  in /home/WASSEX/Semestre2/CPE/CPE_2016_Lemin
** 
** Made by Wassim Alkayar
** Login   <WASSEX@epitech.net>
** 
** Started on  Mon Sep 25 17:10:41 2017 Wassim Alkayar
** Last update Mon Sep 25 19:02:32 2017 Wassim Alkayar
*/

#include "my.h"

t_road          **first_epur(t_road **road)
{
  int           i;
  int           j;

  i = 0;
  j = 0;
  while (road[i])
    {
      j = i + 1;
      while (road[j])
	{
	  if (my_strcmp(road[j]->a, road[j]->b) == 1 &&
	      (my_strcmp(road[j]->a, "void") == 0 ||
	       my_strcmp(road[j]->b, "void") == 0))
	    {
	      road[j]->a = my_strdup("void");
	      road[j]->b = my_strdup("void");
	    }
	  j += 1;
	}
      i += 1;
    }
  return (road);
}

t_road	**second_epur(t_road **road)
{
  int	i;
  int	j;

  i = 0;
  j = 0;
  while (road[i])
    {
      j = i + 1;
      while (road[j])
	{
	  if ((my_strcmp(road[j]->a, road[i]->a) == 1 &&
	       my_strcmp(road[j]->b, road[i]->b) == 1))
	    {
	      road[i]->a = my_strdup("void");
	      road[i]->b = my_strdup("void");
	    }
	  else if ((my_strcmp(road[j]->a, road[i]->b)) == 1 &&
		   (my_strcmp(road[j]->b, road[i]->a)) == 1)
	    {
	      road[i]->a = my_strdup("void");
	      road[i]->b = my_strdup("void");
	    }
	  j += 1;
	}
      i += 1;
    }
  return (road);
}

t_road	**epur_road(t_road **road)
{
  road = first_epur(road);
  road = second_epur(road);
  return (road);
}
