/*
** my_put_nbr.c for my_put_nbr in /home/Wasx/CPool_Day03
** 
** Made by Wassim ALKAYAR
** Login   <Wasx@epitech.net>
** 
** Started on  Wed Mar  1 17:58:17 2017 Wassim ALKAYAR
** Last update Thu Sep 28 18:42:53 2017 Wassim Alkayar
*/

#include <unistd.h>
#include "mysh.h"

void		my_put_nbr(int nb)
{
  int		div;

  div = 1000000000;
  if (nb < 0)
    {
      my_putchar('-');
      nb = nb * (-1);
    }
  if (nb > 0)
    {
      while ((nb / div) == 0)
	div = div / 10;
      while (div != 0)
	{
	  my_putchar(48 + (nb / div) % 10);
	  div = div / 10;
	}
    }
  else
    my_putchar(48);
}
