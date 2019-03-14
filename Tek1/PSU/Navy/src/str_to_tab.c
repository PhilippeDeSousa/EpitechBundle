/*
** str_to_tab.c for  in /home/WASSEX/Semestre2/PSU_2016_navy/src2
** 
** Made by Wassim Alkayar
** Login   <WASSEX@epitech.net>
** 
** Started on  Tue Jun 27 12:12:05 2017 Wassim Alkayar
** Last update Sat Jul  1 17:19:59 2017 Wassim Alkayar
*/

#include "../include/navy.h"

char	**get_complete_tab(char *map, char **tab)
{
  int	i;
  int	j;
  int	k;

  i = 0;
  k = 0;
  while (map[i] != '\0')
    {
      j = 0;
      if ((tab[k] = malloc(sizeof(char) * MAP_LINE_LENGTH)) == NULL)
	return (NULL);
      while (map[i] != '\n')
	{
	  tab[k][j] = map[i];
	  i += 1;
	  j += 1;
	}
      tab[k][j] = '\0';
      k += 1;
      i += 1;
    }
  tab[k] = NULL;
  return (tab);
}

char	**map_to_tab()
{
  char	**tab;
  char	*map;
  int	fd;

  if ((fd = open(MAP_FORMAT_LOCATION, O_RDONLY)) == -1)
    return (NULL);
  map = get_next_line(fd);
  if ((tab = malloc(sizeof(char *) * (MAP_SIZE + 1))) == NULL)
    return (NULL);
  tab = get_complete_tab(map, tab);
  if ((close(fd)) == -1)
    return (NULL);
  return (tab);
}
