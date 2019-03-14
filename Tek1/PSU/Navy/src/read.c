/*
** read.c for navy in /home/philippe/PSU/navy
** 
** Made by Philippe De Sousa
** Login   <philippe.de-sousa-violante@epitech.eu>
** 
** Started on  Mon Jun 26 13:45:49 2017 Philippe De Sousa
** Last update Mon Jul  3 19:07:31 2017 Wassim Alkayar
*/

#include "navy.h"

void	my_putchar(char c)
{
  write (1, &c, 1);
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
      i++;
    }
}

char	*read_pos(char *file)
{
  int		fd;
  char	*s;

  if ((fd = open(file, O_RDONLY)) == -1)
    return (NULL);
  s = get_next_line(fd);
  if ((close(fd)) == -1)
    return (NULL);
  return (s);
}
