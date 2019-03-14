/*
** my_strcat.c for  in /home/WASSEX/Semestre2/PSU/PSU_2016_42sh
** 
** Made by Wassim Alkayar
** Login   <WASSEX@epitech.net>
** 
** Started on  Sat Sep 30 15:47:53 2017 Wassim Alkayar
** Last update Sat Sep 30 15:48:00 2017 Wassim Alkayar
*/

#include "mysh.h"

char	*my_strcat(char *s1, char *s2)
{
  char	*final;
  int	i;
  int	j;

  i = 0;
  j = 0;
  if (s1 == NULL)
    return (s2);
  else if (s2 == NULL)
    return (s1);
  if ((final = malloc(sizeof(char) *
		      (my_strlen(s1) + my_strlen(s2)) + 10)) == NULL)
    return (NULL);
  while (s1[j])
    {
      final[j] = s1[j];
      j += 1;
    }
  while (s2[i])
    final[j++] = s2[i++];
  final[j] = '\0';
  return (final);
}
