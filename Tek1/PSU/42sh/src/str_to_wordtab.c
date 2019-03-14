/*
** str_to_wordtab.c for  in /home/WASSEX/Semestre2/PSU/PSU_2016_42sh/src
** 
** Made by Wassim Alkayar
** Login   <WASSEX@epitech.net>
** 
** Started on  Sun Oct  1 14:13:53 2017 Wassim Alkayar
** Last update Sun Oct  1 17:05:28 2017 Wassim Alkayar
*/

#include <stdlib.h>
#include "mysh.h"

char	**str_to_wordtab(char *str)
{
  char	**tab;
  int	i;
  int	j;
  int	k;

  i = 0;
  k = 0;
  if ((tab = malloc(sizeof(char *) * my_strlen(str)) + 1) == NULL)
    return (NULL);
  while (str[i] != '\0')
    {
      j = 0;
      if ((tab[k] = malloc(sizeof(char) * my_strlen(str))) == NULL)
	return (NULL);
      while (str[i] != '\n' && str[i] != '\0')
	tab[k][j++] = str[i++];
      tab[k][j] = '\0';
      k += 1;
      i += 1;
    }
  tab[k] = NULL;
  return (tab);
}
