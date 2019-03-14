/*
** main.c for navy in /home/philippe/PSU/navy
** 
** Made by Philippe De Sousa
** Login   <philippe.de-sousa-violante@epitech.eu>
** 
** Started on  Mon Jun 26 14:12:31 2017 Philippe De Sousa
** Last update Tue Jul 11 12:29:47 2017 Wassim Alkayar
*/

#include "navy.h"

int	main_suite(int ac, char **av)
{
  char	**board;
  int	gamernum;
  int	i;

  if (ac == 2)
    gamernum = 1;
  else
    gamernum = 2;
  if (ac == 2)
    board = prepare_game(av[1]);
  if (ac == 3)
    board = prepare_game(av[2]);
  i = start_game(board, gamernum);
  free (board);
  return (i);
}

int	main(int ac, char **av)
{
  t_player	*p;

  if (ac == 2 && my_strcmp("-h", av[1]) == 1)
    {
      navy_man();
      return (0);
    }
  if ((ac < 2 || ac > 3) || (ac == 2 && (check_the_map(av[1])) == -1))
    return (84);
  if (ac == 3 && (check_the_map(av[2])) == -1)
    return (84);
  if (!(p = malloc(sizeof(t_player))))
    return (84);
  else if (ac > 1)
    {
      p->player = (ac == 2) ? 1 : 2;
      my_putstr("my_pid:  ");
      my_put_nbr(getpid());
      my_putchar('\n');
      if (connect(av, p) == 0)
	return (84);
    }
  return (main_suite(ac, av));
}
