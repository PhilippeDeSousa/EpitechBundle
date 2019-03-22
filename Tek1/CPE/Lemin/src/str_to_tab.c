/*
** str_to_tab.c for tetris in /home/philippe/PSU/PSU_2016_tetris
** 
** Made by Philippe De Sousa
** Login   <philippe.de-sousa-violante@epitech.eu>
** 
** Started on  Wed Jul 19 12:17:03 2017 Philippe De Sousa
** Last update Fri Sep 22 13:30:33 2017 Wassim Alkayar
*/

#include "my.h"

int	my_strlen(char *s)
{
  int		i;

  i = 0;
  while (s[i])
    i += 1;
  return (i);
}

char	**get_complete_tab(char *map, char **tab)
{
  int	i;
  int	j;
  int	k;

  i = 0;
  k = 0;
  while (i < my_strlen(map))
    {
      j = 0;
      if ((tab[k] = malloc(sizeof(char) * my_strlen(map) + 1)) == NULL)
	return (NULL);
      while (map[i] != '\n' && map[i])
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

char	**str_to_tab(char *str)
{
  char	**tab;

  if (str == NULL)
    return (NULL);
  if ((tab = malloc(sizeof(char *) * (my_strlen(str) + 1))) == NULL)
    return (NULL);
  tab = get_complete_tab(str, tab);
  return (tab);
}
