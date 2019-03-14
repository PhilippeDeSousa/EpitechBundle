/*
** attack.c for navy in /home/philippe/PSU_2016_navy
** 
** Made by Philippe De Sousa
** Login   <philippe.de-sousa-violante@epitech.eu>
** 
** Started on  Fri Jun 30 14:42:25 2017 Philippe De Sousa
** Last update Thu Jul 13 16:56:25 2017 Wassim Alkayar
*/

#include "navy.h"

int	get_num(t_player *p)
{
  p->attack_y = 0;
  sig.signo = SIGUSR1;
  while (sig.signo == SIGUSR1)
    {
      pause();
      p->attack_y = p->attack_y + 1;
    }
  p->attack_x = 0;
  while (sig.signo == SIGUSR2)
    {
      pause();
      p->attack_x = p->attack_x + 1;
    }
  return (1);
}

int	send_attack(int x, int y)
{
  while (y-- > 0)
    {
      if (!send_signal(SIGUSR1))
	return (0);
    }
  while (x-- > 0)
    {
      if (!send_signal(SIGUSR2))
	return (0);
    }
  if (!send_signal(SIGUSR1))
    return (0);
  return (1);
}

int	send_hit_or_miss(t_game *player)
{
  int	x;

  x = 0;
  if (player->hitcheck == 1)
    {
      while (x <= 2)
	{
	  if (!send_signal(SIGUSR1))
	    return (0);
	  x += 1;
	}
      send_signal(SIGUSR2);
    }
  else
    {
      while (x <= 1)
	{
	  if (!send_signal(SIGUSR1))
	    return (0);
	  x += 1;
	}
      send_signal(SIGUSR2);
    }
  return (0);
}

int	get_hit_or_miss()
{
  int	x;

  x = 0;
  sig.signo = SIGUSR1;
  while (sig.signo == SIGUSR1)
    {
      pause();
      x += 1;
    }
  x -= 2;
  return (x);
}
