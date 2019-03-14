/*
** my_atoi.c for  in /home/WASSEX/jungle/pushswapautre/CPE_2016_Pushswap
** 
** Made by Wassim Alkayar
** Login   <WASSEX@epitech.net>
** 
** Started on  Wed Apr 19 01:56:00 2017 Wassim Alkayar
** Last update Thu Jun 29 15:28:44 2017 Philippe De Sousa
*/

#include "navy.h"

int	convertnb(char *str)
{
  int	i;
  int	result;
  int	sign;

  i = 0;
  result = 0;
  sign = 1;
  if (str == NULL)
    return (0);
  if (str[0] == '-')
    {
      sign = -1;
      i = i + 1;
    }
  while (str[i] != '\0')
    {
      result = result * 10 + str[i] - '0';
      i = i + 1;
    }
  return (sign * result);
}
