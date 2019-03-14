/*
** print_double_tab.c for navy in /home/philippe/PSU_2016_navy
** 
** Made by Philippe De Sousa
** Login   <philippe.de-sousa-violante@epitech.eu>
** 
** Started on  Thu Jun 29 16:34:27 2017 Philippe De Sousa
** Last update Wed Apr 18 23:03:37 2018 Philippe
*/

#include "navy.h"

void	print_double_tab(char **tab)
{
  int	i;

  if (tab == NULL)
    return ;
  i = 0;
  while (tab[i] != NULL)
    {
      my_putstr(tab[i]);
      my_putchar('\n');
      i += 1;
    }
}
