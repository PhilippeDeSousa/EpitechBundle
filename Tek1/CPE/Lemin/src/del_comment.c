/*
** del_comment.c for lem_in in /home/maxence.fourrier/Documents/Project_C/CPE_2016_Lemin/src
** 
** Made by maxence.fourrier
** Login   <maxence.fourrier@epitech.eu>
** 
** Started on  Wed Sep  6 15:06:32 2017 maxence.fourrier
** Last update Thu Sep 21 16:41:31 2017 Wassim Alkayar
*/

#include "my.h"

char		*del_comment(char *buff)
{
  char		*ret;
  int		i;
  int		x;

  if ((ret = malloc(sizeof(char) * (my_strlen(buff) + 1))) == NULL)
    return (NULL);
  i = 0;
  x = 0;
  while (buff[i])
    {
      if ((i > 0 && buff[i] == '#' && buff[i + 1] && buff[i + 1] != '#'
           && buff[i - 1] != '#')
          || (i == 0 && buff[i] == '#')
          || (buff[i] == '#' && !buff[i + 1]))
        while (buff[i] && buff[i] != '\n')
          i++;
      else
        ret[x++] = buff[i++];
    }
  ret[x] = 0;
  free(buff);
  return (ret);
}
