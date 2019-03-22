/*
** utils.c for lemin in /home/maxence.fourrier/Documents/Project_C/CPE_2016_Lemin/src
** 
** Made by maxence.fourrier
** Login   <maxence.fourrier@epitech.eu>
** 
** Started on  Wed Sep  6 19:50:25 2017 maxence.fourrier
** Last update Wed Sep  6 21:37:58 2017 maxence.fourrier
*/

#include "my.h"

int		get_x_room(char *str)
{
  char		*num;
  int		i;

  if ((num = malloc(sizeof(char) * (my_strlen(str) + 1))) == NULL)
    return (ERROR);
  i = 0;
  while (str[i] != ' ')
    {
      num[i] = str[i];
      i++;
    }
  num[i] = 0;
  return (my_str_to_int(num));
}
