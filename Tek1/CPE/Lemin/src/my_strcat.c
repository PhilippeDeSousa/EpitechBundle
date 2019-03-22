/*
** my_strcat.c for minishell in /home/philippe/PSU/PSU_2016_minishell1
** 
** Made by Philippe De Sousa
** Login   <philippe.de-sousa-violante@student.42.fr>
** 
** Started on  Thu Jun 15 16:49:23 2017 Philippe De Sousa
** Last update Fri Sep 22 15:28:47 2017 Wassim Alkayar
*/

#include "my.h"

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
