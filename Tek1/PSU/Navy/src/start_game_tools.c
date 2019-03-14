/*
** start_game_tools.c for  in /home/WASSEX/Semestre2/PSU_2016_navy
** 
** Made by Wassim Alkayar
** Login   <WASSEX@epitech.net>
** 
** Started on  Tue Jul  4 16:22:24 2017 Wassim Alkayar
** Last update Thu Jul 13 16:56:16 2017 Wassim Alkayar
*/

#include "navy.h"

int	new_x(char *move, char **board)
{
  int	x;
  int	y;

  x = MARGIN;
  y = 0;
  while (board[y][x] != move[0])
    x++;
  return (x);
}

int	new_y(char *move, char **board)
{
  int	y;

  y = MARGIN;
  while (board[y][0] != move[1])
    y++;
  return (y);
}

int	is_move_ok(char *move)
{
  if (move == NULL)
    return (0);
  if (move[0] < 'A' || move[0] > 'H')
    {
      my_putstr("wrong position\n");
      return (0);
    }
  if (move[1] < '1' || move[1] > '8')
    {
      my_putstr("wrong position\n");
      return (0);
    }
  return (1);
}

void	p1_complete_enemy_tab(t_game *player, char move[2])
{
  int	x;
  int	y;

  x = player->playerattak.attack_y;
  y = player->playerattak.attack_x;
  my_putstr(move);
  if (get_hit_or_miss() == 2)
    {
      my_putstr(": hit\n\n");
      player->ennemyboard[x][y] = 'x';
      player->hitnb += 1;
    }
  else
    {
      if (player->ennemyboard[x][y] != 'x')
	player->ennemyboard[x][y] = 'o';
      my_putstr(": missed\n\n");
    }
}

void	read_buffer(char *move[2])
{
  read(0, *move, READ_SIZE_2);
  while (is_move_ok(*move) == 0)
    {
      my_putstr("attack: ");
      read(0, *move, READ_SIZE_2);
    }
}
