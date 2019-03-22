/*
** del_space.c for lemin in /home/maxence.fourrier/Documents/Project_C/CPE_2016_Lemin/src
** 
** Made by maxence.fourrier
** Login   <maxence.fourrier@epitech.eu>
** 
** Started on  Wed Sep  6 19:11:19 2017 maxence.fourrier
** Last update Fri Sep  8 14:53:46 2017 Philippe De Sousa
*/

#include "my.h"

char		*del_space(char *buff)
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
      if (buff[i] == ' ' && buff[i + 1] && buff[i + 1] != '\n')
	{
	  ret[x++] = buff[i++];
	  while (buff[i] && buff[i] == ' ')
	    i++;
	}
      else if (buff[i] == ' ' && buff[i + 1] && buff[i + 1] == '\n')
	i++;
      else
        ret[x++] = buff[i++];
    }
  ret[x] = 0;
  free(buff);
  return (ret);
}
