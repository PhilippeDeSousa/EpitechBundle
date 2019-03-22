/*
** convertnb.c for  in /home/WASSEX/jungle/CPE_2016_stumper3/src
** 
** Made by Wassim Alkayar
** Login   <WASSEX@epitech.net>
** 
** Started on  Mon Sep 18 16:22:52 2017 Wassim Alkayar
** Last update Thu Sep 21 23:20:55 2017 Wassim Alkayar
*/

#include <stdlib.h>
#include "my.h"
/*
int	get_length(int nb)
{
  int	ct;
  int	i;

  i = nb;
  while (i != 0)
    {
      ct += 1;
      i = i / 10;
    }
  return (ct);
}

char	*convertstr(int nb)
{
  int	i;
  int	mem;
  int	length;
  char	*str;

  length = 0;
  i = 0;
  mem = 0;
  if ((str = malloc(sizeof(char) * 10)) == NULL)
    return (NULL);
  length = get_length(nb);
  while (i < length)
    {
      mem = nb % 10;
      nb = nb / 10;
      str[length - (i + 1)] = mem + '0';
      i += 1;
    }
  str[length] = '\0';
  return (str);
}
*/

char	*convertstr(int nb)
{
  int	i;
  int	mem;
  int	length;
  int	n;
  char	*str;

  i = 0;
  length = 0;
  n = nb;
  if ((str = malloc(sizeof(char) * 100)) == NULL)
    return (NULL);
  while (n != 0)
    {
      length++;
      n /= 10;
    }
  while (i < length)
    {
      mem = nb % 10;
      nb = nb / 10;
      str[length - (i + 1)] = mem + '0';
      i += 1;
    }
  str[length] = '\0';
  return (str);
}
