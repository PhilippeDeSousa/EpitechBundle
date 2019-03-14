/*
** verif_str.c for n4s in /home/philippe/CPE/CPE_2016_n4s/tmp/Need4Stek-master
** 
** Made by Philippe De Sousa
** Login   <philippe.de-sousa-violante@epitech.eu>
** 
** Started on  Sat Oct 14 06:32:04 2017 Philippe De Sousa
** Last update Sun Oct 15 15:24:46 2017 Philippe De Sousa
*/

#include "n4s.h"

char	*rm_dots(char *str)
{
  int	dots;
  int	i;
  int	c;
  char	*tmp;

  dots = 0;
  i = 0;
  if ((tmp = malloc(sizeof(char *) * (strlen(str)))) == NULL)
    return (NULL);
  while (dots != 3 && str[i])
    if (str[i++] == ':')
      dots++;
  c = 0;
  while (str[i] != 0)
    {
      if ((str[i] >= '0' && str[i] <= '9') || str[i] == '.' || str[i] == ':')
	{
	  tmp[c] = str[i];
	  c += 1;
	}
      i += 1;
    }
  tmp[c - 1] = '\0';
  return (tmp);
}
