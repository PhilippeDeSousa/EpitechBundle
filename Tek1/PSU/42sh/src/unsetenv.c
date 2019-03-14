/*
** unsetenv.c for  in /home/WASSEX/Semestre1/PSU/PSU_2016_minishell1
** 
** Made by Wassim Alkayar
** Login   <WASSEX@epitech.net>
** 
** Started on  Wed Jun 14 03:04:51 2017 Wassim Alkayar
** Last update Sun Jun 18 02:44:04 2017 Wassim Alkayar
*/

#include "mysh.h"

void		my_unsetenv(char *occ, t_dlist *envlist)
{
  t_cell	*tmp;

  occ = add_equal_sign(occ);
  tmp = (**envlist).begin;
  while (tmp != NULL)
    {
      if ((my_strcmp(occ, cut_str(tmp->str))) == 0)
	{
	  if (tmp->back == NULL)
	    (**envlist).begin = tmp->next;
	  else
	    tmp->back->next = tmp->next;
	  if (tmp->next == NULL)
	    (**envlist).end = tmp->back;
	  else
	    tmp->next->back = tmp->back;
	}
      tmp = tmp->next;
    }
}

void		prepare_unsetenv(t_dlist envlist, t_dlist buffer_list)
{
  t_cell	*tmp;

  tmp = buffer_list->begin->next;
  while (tmp != NULL)
    {
      my_unsetenv(tmp->str, &envlist);
      tmp = tmp->next;
    }
}
