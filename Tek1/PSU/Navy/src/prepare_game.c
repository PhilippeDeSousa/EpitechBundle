/*
** prepare_game.c for navy in /home/philippe/PSU_2016_navy
** 
** Made by Philippe De Sousa
** Login   <philippe.de-sousa-violante@epitech.eu>
** 
** Started on  Thu Jun 29 16:34:53 2017 Philippe De Sousa
** Last update Wed Jul  5 02:05:32 2017 Wassim Alkayar
*/

#include "navy.h"

char	**prepare_game(char *av)
{
  char	*pos;
  char	**board;

  board = map_to_tab();
  pos = get_pos(read_pos(av), 0);
  board = prepare_print_boats(board, pos);
  return (board);
}
