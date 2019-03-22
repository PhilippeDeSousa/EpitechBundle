/*
** check_buff.c for lemin in /home/maxence.fourrier/Documents/Project_C/CPE_2016_Lemin/src
** 
** Made by maxence.fourrier
** Login   <maxence.fourrier@epitech.eu>
** 
** Started on  Wed Sep  6 13:33:08 2017 maxence.fourrier
** Last update Wed Sep  6 19:15:26 2017 maxence.fourrier
*/

#include "my.h"

char		*clean_buff(char *buff)
{
  char		*ret1;
  char		*ret2;
  char		*ret3;

  if ((ret1 = del_comment(buff)) == NULL
      || (ret2 = del_line(ret1)) == NULL
      || (ret3 = del_space(ret2)) == NULL)
    return (NULL);
  return (ret3);
}

char		*check_buff(char *buff)
{
  char		*new;

  if ((new = clean_buff(buff)) == NULL)
    return (NULL);
  return (new);
}
