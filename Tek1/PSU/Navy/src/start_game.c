/*
** start_game.c for navy in /home/philippe/PSU_2016_navy/src
** 
** Made by Philippe De Sousa
** Login   <philippe.de-sousa-violante@epitech.eu>
** 
** Started on  Wed Jun 28 21:01:18 2017 Philippe De Sousa
** Last update Thu Jul 13 14:53:02 2017 Wassim Alkayar
*/

#include "navy.h"

int	check_win_or_loose(t_game *player)
{
  if (player->enemyhitnb == 14)
    {
      send_hit_or_miss(player);
      my_putchar('\n');
      print_players_pos(player);
      my_putstr(LOOSE);
      return (1);
    }
  else if (player->hitnb == 14)
    {
      print_players_pos(player);
      my_putstr(WIN);
      return (0);
    }
  return (2);
}

void	init_player2(t_game *player)
{
  my_putstr(WAIT_ATTACK);
  get_num(&player->enemyattak);
  print_attack(player);
  if (player->hitcheck == 1)
    player->enemyhitnb += 1;
  print_hit_or_miss(player);
  send_hit_or_miss(player);
}

int	player2(t_game *player, char move[2], char **board, int i)
{
  init_player2(player);
  while (player->hitnb < 14)
    {
      my_putstr("\nattack: ");
      read_buffer(&move);
      move[2] = '\0';
      player->playerattak.attack_x = new_x(move, board);
      player->playerattak.attack_y = new_y(move, board);
      send_attack(player->playerattak.attack_x, player->playerattak.attack_y);
      p1_complete_enemy_tab(player, move);
      if ((i = (check_win_or_loose(player))) != 2)
	return (i);
      print_players_pos(player);
      my_putstr(WAIT_ATTACK);
      get_num(&player->enemyattak);
      print_attack(player);
      if (player->hitcheck == 1)
	player->enemyhitnb += 1;
      print_hit_or_miss(player);
      if ((i = (check_win_or_loose(player))) != 2)
	return (i);
      send_hit_or_miss(player);
    }
  return (0);
}

int	player1(t_game *player, char move[2], char **board, int i)
{
  while (player->hitnb < 14)
    {
      my_putstr("attack: ");
      read_buffer(&move);
      move[2] = '\0';
      player->playerattak.attack_x = new_x(move, board);
      player->playerattak.attack_y = new_y(move, board);
      send_attack(player->playerattak.attack_x, player->playerattak.attack_y);
      p1_complete_enemy_tab(player, move);
      if ((i = (check_win_or_loose(player))) != 2)
	return (i);
      my_putstr(WAIT_ATTACK);
      get_num(&player->enemyattak);
      print_attack(player);
      if (player->hitcheck == 1)
	player->enemyhitnb += 1;
      print_hit_or_miss(player);
      if ((i = (check_win_or_loose(player))) != 2)
	return (i);
      my_putchar('\n');
      print_players_pos(player);
      send_hit_or_miss(player);
    }
  return (0);
}

int		start_game(char **board, int gamernum)
{
  t_game	player;
  char		move[2];
  int		i;

  i = 0;
  init_game(&player, board);
  print_players_pos(&player);
  if (gamernum == 1)
    i = player1(&player, move, board, i);
  else if (gamernum == 2)
    i = player2(&player, move, board, i);
  return (i);
}
