/*
** check_map.c for  in /home/WASSEX/Semestre2/PSU_2016_navy/src2
** 
** Made by Wassim Alkayar
** Login   <WASSEX@epitech.net>
** 
** Started on  Wed Jun 28 23:56:06 2017 Wassim Alkayar
** Last update Thu Jul 20 17:43:33 2017 Wassim Alkayar
*/

#include "navy.h"

int	fourth_gate(char *pos)
{
  char	*tmp;
  int	i;
  int	j;
  int	mem;

  i = 0;
  j = 0;
  tmp = get_pos(pos, 0);
  while (i <= 3)
    {
      mem = tmp[j] - '0';
      if (mem != ((tmp[j + 5] - '0') - (tmp[j + 2] - '0') + 1) &&
	  mem != ((tmp[j + 6] - '0') - (tmp[j + 3] - '0') + 1))
	return (-1);
      j += POS_LINE_LENGTH;
      i += 1;
    }
  return (0);
}

int	third_gate(char *pos, int i)
{
  int	two;
  int	three;
  int	four;
  int	five;

  two = 0;
  three = 0;
  four = 0;
  five = 0;
  i = 0;
  while (i < 4)
    {
      if ((pos[0 + (POS_LINE_LENGTH * i)] - '0') == 2)
	two += 1;
      if ((pos[0 + (POS_LINE_LENGTH * i)] - '0') == 3)
	three += 1;
      if ((pos[0 + (POS_LINE_LENGTH * i)] - '0') == 4)
	four += 1;
      if ((pos[0 + (POS_LINE_LENGTH * i)] - '0') == 5)
	five += 1;
      i += 1;
    }
  if (two != 1 || three != 1 || four != 1 || five != 1)
    return (-1);
  return (0);
}

int	second_gate(char *pos)
{
  int	i;
  int	j;

  i = 0;
  j = 0;
  while (i < 4)
    {
      if (pos[j + 1] != ':' || pos[j + 4] != ':')
	return (-1);
      if ((pos[j + 2] < 'A' || pos[j + 2] > 'H') &&
	  (pos[j + 4] < 'A' || pos[j + 2] > 'H'))
	return (-1);
      if ((pos[j + 3] - '0') < 1 || (pos[j + 3] - '0') > 8 ||
	  (pos[j + 6] - '0') < 1 || (pos[j + 6] - '0') > 8)
	return (-1);
      if (i != 3 && pos[j + 7] != '\n')
	return (-1);
      if (pos[j + 2] != pos[j + 5] && pos[j + 3] != pos[j + 6])
	return (-1);
      i += 1;
      j += POS_LINE_LENGTH;
    }
  return (0);
}

int	first_gate(char *pos)
{
  int	i;
  int	j;

  i = 0;
  j = 0;
  while (pos[i] != '\0')
    {
      if ((pos[i] < '0' && pos[i] != '\n') || (pos[i] > ':' && pos[i] < 'A') ||
	  (pos[i] > 'Z'))
	return (-1);
      i += 1;
    }
  i = 0;
  while (i < 4)
    {
      if ((pos[j] - '0') < 2 || (pos[j] - '0') > 5)
	return (-1);
      i += 1;
      j += POS_LINE_LENGTH;
    }
  return (0);
}

int	check_the_map(char *map)
{
  int	fd;
  char	*pos;
  int	i;

  i = 0;
  if ((fd = open(map, O_RDONLY)) == -1)
    return (-1);
  pos = get_next_line(fd);
  if (my_strlen(pos) != 31 && my_strlen(pos) != 32)
    return (-1);
  if ((first_gate(pos)) == -1)
    return (-1);
  if ((second_gate(pos)) == -1)
    return (-1);
  if ((third_gate(pos, i)) == -1)
    return (-1);
  if ((fourth_gate(pos)) == -1)
    return (-1);
  return (0);
}
