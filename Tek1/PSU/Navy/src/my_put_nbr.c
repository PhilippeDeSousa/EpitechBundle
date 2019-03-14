/*
** my_put_nbr.c for navy in /home/philippe/PSU_2016_navy
** 
** Made by Philippe De Sousa
** Login   <philippe.de-sousa-violante@epitech.eu>
** 
** Started on  Thu Jun 29 18:00:19 2017 Philippe De Sousa
** Last update Tue Jul  4 16:34:53 2017 Wassim Alkayar
*/

#include "navy.h"

void	my_put_nbr(int nb)
{
  int	m;

  if (nb < 0)
    {
      nb = - 1 * nb;
      my_putchar('-');
    }
  if (nb < 10)
    {
      my_putchar(nb + 48);
    }
  if (nb > 10)
    {
      my_put_nbr(nb / 10);
      m = nb % 10;
      my_putchar(m + 48);
    }
}
