/*
** start_game_tools2.c for  in /home/WASSEX/Semestre2/PSU_2016_navy
** 
** Made by Wassim Alkayar
** Login   <WASSEX@epitech.net>
** 
** Started on  Tue Jul  4 16:27:39 2017 Wassim Alkayar
** Last update Thu Jul 13 17:04:47 2017 Wassim Alkayar
*/

#include "navy.h"

void	print_players_pos(t_game *player)
{
  my_putstr("my positions:\n");
  print_double_tab(player->playerboard);
  my_putchar('\n');
  my_putstr("enemy's positions:\n");
  print_double_tab(player->ennemyboard);
  my_putchar('\n');
}

void	init_game(t_game *player, char **board)
{
  player->hitnb = 0;
  player->enemyhitnb = 0;
  player->playerboard = board;
  player->ennemyboard = map_to_tab();
}

void	print_attack(t_game *player)
{
  int	x;
  int	y;

  y = player->enemyattak.attack_x;
  x = player->enemyattak.attack_y - 1;
  if (player->playerboard[x][y] == 'x')
    player->hitcheck = 0;
  else if (player->playerboard[x][y] == '.')
    {
      player->playerboard[x][y] = 'o';
      player->hitcheck = 0;
    }
  else if (player->playerboard[x][y] == 'o')
    player->hitcheck = 0;
  else
    {
      player->playerboard[x][y] = 'x';
      player->hitcheck = 1;
    }
}

void	print_hit_or_miss(t_game *player)
{
  char	bloc[2];
  int	x;
  int	y;

  x = player->enemyattak.attack_x / 2;
  y = player->enemyattak.attack_y - 2;
  if (x == 0)
    bloc[0] = 'A';
  else
    bloc[0] = 64 + x;
  if (y == 0)
    bloc[1] = '1';
  else
    bloc[1] = y + '0';
  bloc[2] = '\0';
  my_putstr(bloc);
  my_putstr(":");
  if (player->hitcheck == 1)
    my_putstr(" hit\n");
  else
    my_putstr(" missed\n");
}
