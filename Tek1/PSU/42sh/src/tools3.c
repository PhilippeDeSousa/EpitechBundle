/*
** tools3.c for  in /home/WASSEX/Semestre1/PSU/PSU_2016_minishell1/src
** 
** Made by Wassim Alkayar
** Login   <WASSEX@epitech.net>
** 
** Started on  Tue Jun 20 19:04:47 2017 Wassim Alkayar
** Last update Fri Sep  1 13:51:24 2017 Wassim Alkayar
*/

#include "mysh.h"

int	check_non_alpha(char *str)
{
  int	i;

  i = 0;
  while (str[i] != '\0')
    {
      if (str[i] < '0' || (str[i] > '9' && str[i] < 'A') ||
	  (str[i] > 'Z' && str[i] < 'a') || str[i] > 'z')
	return (2);
      i += 1;
    }
  return (0);
}
