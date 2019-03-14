/*
** env.c for  in /home/WASSEX/Semestre1/PSU/PSU_2016_minishell1
** 
** Made by Wassim Alkayar
** Login   <WASSEX@epitech.net>
** 
** Started on  Tue Jun 13 16:01:28 2017 Wassim Alkayar
** Last update Wed Jun 14 18:38:00 2017 Wassim Alkayar
*/

#include "mysh.h"

void		env(t_dlist envlist)
{
  t_cell	*tmp;

  tmp = envlist->begin;
  while (tmp != NULL)
    {
      my_putstr(tmp->str);
      my_putchar('\n');
      tmp = tmp-> next;
    }
}
