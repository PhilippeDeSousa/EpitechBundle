/*
** get_buff.c for lemin in /home/maxence.fourrier/Documents/Project_C/CPE_2016_Lemin/src
** 
** Made by maxence.fourrier
** Login   <maxence.fourrier@epitech.eu>
** 
** Started on  Wed Sep  6 12:48:20 2017 maxence.fourrier
** Last update Wed Sep 20 12:08:21 2017 Wassim Alkayar
*/

#include <fcntl.h>
#include "my.h"

int		get_size_file()
{
  int		i;
  char		c;

  i = 0;
  while (read(0, &c, 1) > 0)
    i++;
  return (i);
}

char		*get_buff()
{
  char		*buff;
  int		taille;
  int		pos;

  if ((taille = get_size_file()) == -1)
    return (NULL);
  if ((buff = malloc(sizeof(char) * (taille + 1))) == NULL)
    return (NULL);
  if ((pos = read(0, buff, taille)) == -1)
    return (NULL);
  buff[taille] = '\0';
  return (buff);
}
