/*
** my_strdup.c for  in /home/WASSEX/Semestre2/CPE/CPE_2016_Lemin/src
** 
** Made by Wassim Alkayar
** Login   <WASSEX@epitech.net>
** 
** Started on  Wed Sep 20 14:37:33 2017 Wassim Alkayar
** Last update Wed Sep 20 14:38:45 2017 Wassim Alkayar
*/

#include "my.h"

char	*my_strdup(char *str)
{
  int	i;
  char	*new;

  i = 0;
  if ((new = malloc(sizeof(char) * my_strlen(str) + 1)) == NULL)
    return (NULL);
  while (str[i] != '\0')
    {
      new[i] = str[i];
      i += 1;
    }
  new[i] = '\0';
  return (new);
}
