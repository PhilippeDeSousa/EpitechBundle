/*
** get_pos.c for lemin in /home/philippe/CPE_2016_Lemin
** 
** Made by Philippe De Sousa
** Login   <philippe.de-sousa-violante@epitech.eu>
** 
** Started on  Fri Sep  8 13:15:29 2017 Philippe De Sousa
** Last update Fri Sep 22 13:36:23 2017 Wassim Alkayar
*/

#include "my.h"

int		is_end(char *buff, int i)
{
  char		*tmp;
  int		c;

  c = 0;
  tmp = malloc(sizeof(char) * (my_strlen(buff)));
  while (buff[i] != '\n' && buff[i])
    {
      tmp[c] = buff[i];
      i++;
      c++;
    }
  tmp[c] = '\0';
  if ((my_strcmp(tmp, "##end")) == 1)
    {
      free(tmp);
      return (1);
    }
  else
    {
      free(tmp);
      return (0);
    }
}

char	*first_nb(char *buffer)
{
  char	*tmp;
  int	i;

  if ((tmp = malloc(sizeof(char) * my_strlen(buffer) + 1)) == NULL)
    return (NULL);
  i = 0;
  while (buffer[i] != ' ' && buffer[i])
    {
      tmp[i] = buffer[i];
      i += 1;
    }
  tmp[i] = '\0';
  return (tmp);
}

char	*get_end(char **buffer)
{
  int	i;

  i = 0;
  while ((my_strcmp(buffer[i], "##end")) != 1)
    i += 1;
  return (first_nb(buffer[i + 1]));
}

char	*get_start(char **buffer)
{
  int	i;

  i = 0;
  while ((my_strcmp(buffer[i], "##start")) != 1)
    i += 1;
  return (first_nb(buffer[i + 1]));
}
