/*
** tools.c for tools in /home/Max/Documents/src
** 
** Made by fourrier maxence
** Login   <maxence.fourrier@epitech.eu>
** 
** Started on  Tue May 16 10:17:17 2017 fourrier maxence
** Last update Wed Sep 20 14:37:27 2017 Wassim Alkayar
*/

#include "my.h"

char		*get_line(char **buff)
{
  char		*ret;
  int		i;

  i = 0;
  while ((*buff)[i] && (*buff)[i] != '\n')
    i++;
  if (i == 0)
    return (NULL);
  if ((ret = malloc(sizeof(char) * (i + 1))) == NULL)
    return (NULL);
  i = 0;
  while ((*buff)[i] && (*buff)[i] != '\n')
    {
      ret[i] = (*buff)[i];
      i++;
    }
  ret[i] = 0;
  if ((*buff)[i] == 0)
    *buff = NULL;
  else
    *buff = *buff + i + 1;
  return (ret);
}

int		is_number(char *str)
{
  int		i;

  i = 0;
  while (str[i])
    {
      if (!is_num(str[i]))
	return (SUCCESS);
      i++;
    }
  return (1);
}

int		is_num(char c)
{
  if (c >= '0' && c <= '9')
    return (1);
  return (SUCCESS);
}

int		is_char(char c)
{
  if ((c >= 'a' && c <= 'z')
      || (c >= 'A' && c <= 'Z'))
    return (1);
  return (SUCCESS);
}
