/*
** functions.c for n4s in /home/philippe/CPE/CPE_2016_n4s
** 
** Made by Philippe De Sousa
** Login   <philippe.de-sousa-violante@epitech.eu>
** 
** Started on  Sat Oct 14 13:38:37 2017 Philippe De Sousa
** Last update Sat Oct 14 17:21:41 2017 Philippe De Sousa
*/

#include "n4s.h"

void	my_putchar(int fd, char c)
{
  write(fd, &c, 1);
}

void	my_putstr(int fd, char *str)
{
  int	i;

  i = 0;
  while (str[i])
    {
      my_putchar(fd, str[i]);
      i += 1;
    }
}

int	my_strlen(char *str)
{
  int	i;

  i = 0;
  while (str[i])
    i += 1;
  return (i);
}
