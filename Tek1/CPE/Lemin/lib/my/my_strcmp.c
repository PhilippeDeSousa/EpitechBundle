/*
** my_strcmp.c for my_strcmp in /home/Max/Documents/delivery/PSU_2016_my_ls/lib/my
** 
** Made by fourrier maxence
** Login   <maxence.fourrier@epitech.eu>
** 
** Started on  Tue Apr 18 15:57:07 2017 fourrier maxence
** Last update Thu Sep 21 15:39:46 2017 Wassim Alkayar
*/

#include "my.h"

int	my_strcmp(char *a, char *b)
{
  int	i;

  i = 0;
  if (my_strlen(a) != my_strlen(b))
    return (0);
  while (i != my_strlen(a))
    {
      if (a[i] == b[i])
	i++;
      else
	return (0);
    }
  return (1);
}
