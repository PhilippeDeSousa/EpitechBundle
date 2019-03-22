/*
** init.c for lemin in /home/maxence.fourrier/Documents/Project_C/CPE_2016_Lemin/src
** 
** Made by maxence.fourrier
** Login   <maxence.fourrier@epitech.eu>
** 
** Started on  Wed Sep  6 15:29:57 2017 maxence.fourrier
** Last update Mon Sep 25 15:22:14 2017 Wassim Alkayar
*/

#include "my.h"

int		is_road(char *line)
{
  int		i;
  int		save;

  i = 0;
  while (line[i] && line[i] != '-')
    i++;
  if (!line[i] || i == 0 || line[i] != '-')
    return (ERROR);
  save = i;
  while (line[i])
    i++;
  if (save == i)
    return (ERROR);
  return (SUCCESS);
}

int		nb_road(char *buff)
{
  char		*ret;
  int		i;

  i = 0;
  while (buff != NULL && (ret = get_line(&buff)) != NULL)
    {
      if (is_road(ret) != ERROR)
	i++;
      free(ret);
    }
  return (i);
}

t_road		*my_link_road(char *ret)
{
  t_road	*new;
  int		i;
  int		x;

  if ((new = malloc(sizeof(t_road))) == NULL
      || (new->a = malloc(sizeof(char) * (my_strlen(ret) + 1))) == NULL
      || (new->b = malloc(sizeof(char) * (my_strlen(ret) + 1))) == NULL)
    return (NULL);
  i = 0;
  x = 0;
  while (ret[i] != '-')
    {
      new->a[i] = ret[i];
      i++;
    }
  new->a[i] = 0;
  i++;
  while (ret[i])
    new->b[x++] = ret[i++];
  new->b[x] = 0;
  return (new);
}

int		check_road(char *line)
{
  int		i;
  int		cpt;

  i = -1;
  cpt = 0;
  while (line[++i] && line[++i] != '\n')
    if (line[i] == '-')
      cpt++;
  if (cpt > 1)
    return (1);
  return (SUCCESS);
}

t_road		**init_road(char *buff)
{
  char		*ret;
  t_road	**road;
  int		i;

  if ((road = malloc(sizeof(t_road *) * (nb_road(buff) + 1))) == NULL
      || check_road(buff))
    return (NULL);
  i = 0;
  while (buff != NULL && (ret = get_line(&buff)) != NULL)
    {
      if (is_road(ret) != ERROR)
	{
	  if ((road[i] = my_link_road(ret)) == NULL
	      || check_road(ret))
	    return (NULL);
	  i++;
	}
      else if (is_room(ret) == ERROR && !is_number(ret)
	       && ret != NULL && ret[0] != '#')
	return (NULL);
      free(ret);
    }
  road[i] = NULL;
  return (road);
}
