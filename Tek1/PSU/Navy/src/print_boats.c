/*
** print_boats.c for  in /home/WASSEX/Semestre2/PSU_2016_navy/src2
** 
** Made by Wassim Alkayar
** Login   <WASSEX@epitech.net>
** 
** Started on  Tue Jun 27 22:36:31 2017 Wassim Alkayar
** Last update Wed Jun 28 19:05:12 2017 Wassim Alkayar
*/

#include "navy.h"

char	**print_boats(char **tab, t_vector begin, t_vector end, char size)
{
  int	i;

  i = 1;
  while (i <= (size - '0'))
    {
      tab[MARGIN + begin.y][MARGIN + (begin.x * 2)] = size;
      if (begin.x != end.x)
	begin.x += 1;
      if (begin.y != end.y)
	begin.y += 1;
      i += 1;
    }
  return (tab);
}

char		**prepare_print_boats(char **tab, char *pos)
{
  t_vector	begin;
  t_vector	end;
  char		size;
  int		i;
  int		j;

  j = 0;
  i = 0;
  while (i != 4)
    {
      size = pos[0 + j];
      begin.x = pos[2 + j] - '0' - 1;
      begin.y = pos[3 + j] - '0' - 1;
      end.x = pos[5 + j] - '0' - 1;
      end.y = pos[6 + j] - '0' - 1;
      j += POS_LINE_LENGTH;
      tab = print_boats(tab, begin, end, size);
      i += 1;
    }
  return (tab);
}
