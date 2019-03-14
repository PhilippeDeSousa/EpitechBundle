/*
** repeat.c for  in /home/WASSEX/Semestre2/PSU/PSU_2016_42sh
** 
** Made by Wassim Alkayar
** Login   <WASSEX@epitech.net>
** 
** Started on  Wed Oct  4 22:08:29 2017 Wassim Alkayar
** Last update Fri Oct  6 22:57:59 2017 Wassim Alkayar
*/

#include "mysh.h"

int		is_num(char *str)
{
  int		i;

  i = 0;
  while (str[i])
    {
      if (str[i] < '0' || str[i] > '9')
	return (1);
      i += 1;
    }
  return (0);
}

void		execute_repeat(t_shell *sh)
{
  int		ct;

  ct = convertnb(sh->buffer_list->begin->next->str);
  sh->buffer_list->begin = sh->buffer_list->begin->next->next;
  sh->buffer_list->begin->back = NULL;
  while (ct >= 1)
    {
      first_commands(sh);
      ct--;
    }
}

void		repeat(t_shell *sh)
{
  t_cell	*tmp;

  tmp = sh->buffer_list->begin;
  if (sh->buffer_list->length < 3)
    {
      my_putstr("repeat: Too few arguments.\n");
      sh->retvalue = 1;
      return ;
    }
  if ((is_num(tmp->next->str)) == 1)
    {
      my_putstr("repeat: Badly formed number.\n");
      sh->retvalue = 1;
      return ;
    }
  execute_repeat(sh);
}
