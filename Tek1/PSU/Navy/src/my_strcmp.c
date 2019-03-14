/*
** my_strcmp.c for pushswap in /home/philippe/delivery/CPool_Day
** 
** Made by Philippe De Sousa
** Login   <philippe.de-sousa-violante@epitech.eu>
** 
** Started on  Tue Apr 18 15:20:33 2017 Philippe De Sousa
** Last update Tue Jun 27 12:11:05 2017 Philippe De Sousa
*/

#include "navy.h"

int	my_strcmp(char *s1, char *s2)
{
  int	i;

  i = 0;
  if (my_strlen(s1) != my_strlen(s2))
    return (0);
  while (i != my_strlen(s1))
    {
      if (s1[i] == s2[i])
	i++;
      else
	return (0);
    }
  return (1);
}
