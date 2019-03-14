/*
** get_pos.c for  in /home/WASSEX/Semestre2/PSU_2016_navy/src2
** 
** Made by Wassim Alkayar
** Login   <WASSEX@epitech.net>
** 
** Started on  Tue Jun 27 22:23:35 2017 Wassim Alkayar
** Last update Thu Jul 20 17:36:40 2017 Wassim Alkayar
*/

#include "../include/navy.h"

char	*get_pos(char *pos, int i)
{
  if (pos == NULL)
    return (pos);
  while (pos[i] != '\0')
    {
      if (pos[i] == 'A')
	pos[i] = '1';
      if (pos[i] == 'B')
	pos[i] = '2';
      if (pos[i] == 'C')
	pos[i] = '3';
      if (pos[i] == 'D')
	pos[i] = '4';
      if (pos[i] == 'E')
	pos[i] = '5';
      if (pos[i] == 'F')
	pos[i] = '6';
      if (pos[i] == 'G')
	pos[i] = '7';
      if (pos[i] == 'H')
	pos[i] = '8';
      i += 1;
    }
  return (pos);
}
