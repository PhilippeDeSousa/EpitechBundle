/*
** tab_size.c for tetris in /home/philippe/PSU/PSU_2016_tetris
** 
** Made by Philippe De Sousa
** Login   <philippe.de-sousa-violante@epitech.eu>
** 
** Started on  Mon Jul 24 19:36:22 2017 Philippe De Sousa
** Last update Sun Sep 10 15:15:32 2017 Philippe De Sousa
*/

#include "my.h"

int	tab_size(t_road **road)
{
  int	l;

  l = 0;
  while (road[l])
    l++;
  return (l);
}
