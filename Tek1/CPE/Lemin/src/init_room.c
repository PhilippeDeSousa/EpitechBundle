/*
** init_room.c for lemin in /home/maxence.fourrier/Documents/Project_C/CPE_2016_Lemin/src
** 
** Made by maxence.fourrier
** Login   <maxence.fourrier@epitech.eu>
** 
** Started on  Wed Sep  6 19:01:13 2017 maxence.fourrier
** Last update Mon Sep 25 15:18:05 2017 Wassim Alkayar
*/

#include "my.h"

int		is_room(char *line)
{
  int		i;
  int		save;

  i = 0;
  while (line[i] && line[i] != ' ')
    i++;
  if (!line[i] || i == 0 || line[i] != ' ')
    return (ERROR);
  save = i;
  while (line[++i] && line[i] != ' ')
    if (!is_num(line[i]))
      return (ERROR);
  if (!line[i] || line[i] != ' ' || save == i)
    return (ERROR);
  save = i;
  while (line[++i] && line[i] != ' ')
    if (!is_num(line[i]))
      return (ERROR);
  if (line[i] || save == i || i < 5)
    return (ERROR);
  return (SUCCESS);
}

int		nb_room(char *buff)
{
  char		*ret;
  int		i;

  i = 0;
  while (buff != NULL && (ret = get_line(&buff)) != NULL)
    {
      if (is_room(ret) != ERROR)
        i++;
      free(ret);
    }
  return (i);
}

t_room		*my_link_room(char *ret)
{
  t_room	*new;
  int		i;

  if ((new = malloc(sizeof(t_road))) == NULL
      || (new->room = malloc(sizeof(char) * (my_strlen(ret) + 1))) == NULL)
    return (NULL);
  i = 0;
  while (ret[i] != ' ')
    {
      new->room[i] = ret[i];
      i++;
    }
  new->room[i] = 0;
  i++;
  new->x = get_x_room(ret + i);
  while (ret[i] != ' ')
    i++;
  i++;
  new->y = my_str_to_int(ret + i);
  return (new);
}

t_room		**init_room(char *buff)
{
  char		*ret;
  t_room	**room;
  int		i;

  if ((room = malloc(sizeof(t_room *) * (nb_room(buff) + 1))) == NULL)
    return (NULL);
  i = 0;
  while (buff != NULL && (ret = get_line(&buff)) != NULL)
    {
      if (is_room(ret) != ERROR)
	{
          if ((room[i] = my_link_room(ret)) == NULL)
	    return (NULL);
          i++;
        }
      free(ret);
    }
  room[i] = 0;
  return (room);
}
