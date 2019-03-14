/*
** basicfcts.c for  in /home/WASSEX/Semestre1/PSU/PSU_2016_minishell1
** 
** Made by Wassim Alkayar
** Login   <WASSEX@epitech.net>
** 
** Started on  Mon Jun 12 16:49:09 2017 Wassim Alkayar
** Last update Wed Oct  4 23:08:42 2017 Wassim Alkayar
*/

#include "mysh.h"

void	my_putchar(char c)
{
  write(1, &c, 1);
}

void	my_putstr(char *str)
{
  int	i;

  if (str == NULL)
    return ;
  i = 0;
  while (str[i] != '\0')
    {
      my_putchar(str[i]);
      i += 1;
    }
}

int	my_strlen(char *str)
{
  int	i;

  i = 0;
  while (str[i] != '\0')
    i += 1;
  return (i);
}

int	my_strcmp(char *str1, char *str2)
{
  int	i;

  i = 0;
  if (str1 == NULL || str2 == NULL)
    return (-1);
  while (str1[i] == str2[i])
    {
      if (str1[i] == '\0')
	return (0);
      i += 1;
    }
  return (-1);
}

char	*my_strdup(char *str)
{
  int	i;
  char	*new;

  if (str == NULL)
    return (NULL);
  i = 0;
  if ((new = malloc(sizeof(char) * (my_strlen(str) + 1))) == NULL)
    return (NULL);
  while (str[i] != '\0')
    {
      new[i] = str[i];
      i += 1;
    }
  new[i] = '\0';
  return (new);
}
