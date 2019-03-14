/*
** server.c for navy in /home/philippe/PSU_2016_navy
** 
** Made by Philippe De Sousa
** Login   <philippe.de-sousa-violante@epitech.eu>
** 
** Started on  Thu Jun 29 17:36:59 2017 Philippe De Sousa
** Last update Thu Jul 13 16:44:20 2017 Wassim Alkayar
*/

#include "navy.h"

void	sig_action(int signo, siginfo_t *sinfo, void *context)
{
  if (sig.enemy_pid == 0)
    sig.enemy_pid =(int)sinfo->si_pid;
  sig.signo = signo;
  (void)(context);
}

int	get_signal(int signum)
{
  struct sigaction	act;

  act.sa_flags = SA_SIGINFO;
  act.sa_sigaction = sig_action;
  sigemptyset(&act.sa_mask);
  if (!!sigaction(signum, &act, NULL))
    {
      write(2, FAIL_SIGNAL_HANDLE, 25);
      return (-1);
    }
  return (1);
}

int	send_signal(int signum)
{
  if (!!usleep(WAIT))
    {
      write (2, FAIL_USLEEP, 19);
      return (0);
    }
  if (kill(sig.enemy_pid, signum))
    {
      write (2, FAIL_SIGNAL_SEND, 23);
      return (0);
    }
  return (1);
}

int	connect(char **av, t_player *p)
{
  if ((!get_signal(SIGUSR1) || !get_signal(SIGUSR2)))
    return (0);
  if (p->player == 1)
    {
      my_putstr(WAIT_CONNECTION);
      if ((!pause() || !send_signal(SIGUSR1)))
	return (0);
      my_putstr(ENEMY_CONNECTED);
    }
  else if (p->player == 2)
    {
      sig.enemy_pid = convertnb(av[1]);
      if ((!send_signal(SIGUSR1) || !pause()))
	return (0);
      my_putstr(CONNECTED);
    }
  return (1);
}
