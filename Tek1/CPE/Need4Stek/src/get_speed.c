/*
** ia.c for n4s in /home/philippe/CPE/CPE_2016_n4s/tmp/Need4Stek-master
** 
** Made by Philippe De Sousa
** Login   <philippe.de-sousa-violante@epitech.eu>
** 
** Started on  Sat Oct 14 06:32:04 2017 Philippe De Sousa
** Last update Sun Oct 15 21:43:49 2017 Philippe De Sousa
*/

#include "n4s.h"

int	get_speed(float mid)
{
  int	move;

  if (mid >= 1900)
    move = exec(SPEED_1_0);
  else if (mid >= 1400)
    move = exec(SPEED_0_8);
  else if (mid >= 900)
    move = exec(SPEED_0_5);
  else if (mid >= 500)
    move = exec(SPEED_0_4);
  else if (mid >= 300)
    move = exec(SPEED_0_2);
  else
    move = exec(SPEED_0_1);
  return (move);
}
