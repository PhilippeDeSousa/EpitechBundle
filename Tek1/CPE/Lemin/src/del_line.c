/*
** del_back.c for lemin in /home/maxence.fourrier/Documents/Project_C/CPE_2016_Lemin/src
** 
** Made by maxence.fourrier
** Login   <maxence.fourrier@epitech.eu>
** 
** Started on  Wed Sep  6 15:01:32 2017 maxence.fourrier
** Last update Wed Sep  6 16:10:09 2017 maxence.fourrier
*/

#include "my.h"

char		*del_line_in(char *buff, char *ret, int *i, int *x)
{
  if ((*i == 0 && buff[*i] == '\n') || (buff[*i] == '\n' && !buff[*i + 1]))
    while (buff[*i] && buff[*i] == '\n')
      (*i)++;
  else if (buff[*i] && buff[*i] == '\n')
    {
      ret[*x] = buff[*i];
      *x = *x + 1;
      *i = *i + 1;
      while (buff[*i] && buff[*i] == '\n')
        *i = *i + 1;
    }
  else
    {
      ret[*x] = buff[*i];
      *x = *x + 1;
      *i = *i + 1;
    }
  return (ret);
}

char		*del_line(char *buff)
{
  char		*ret;
  int		i;
  int		x;

  if ((ret = malloc(sizeof(char) * (my_strlen(buff) + 1))) == NULL)
    return (NULL);
  i = 0;
  x = 0;
  while (buff[i])
    ret = del_line_in(buff, ret, &i, &x);
  if (x > 0 && ret[x - 1] == '\n')
    ret[x - 1] = 0;
  else
    ret[x] = 0;
  free(buff);
  return (ret);
}
