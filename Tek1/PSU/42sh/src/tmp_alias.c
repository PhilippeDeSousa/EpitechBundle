/*
** tmp_alias.c for  in /home/WASSEX/Semestre2/PSU/PSU_2016_42sh
** 
** Made by Wassim Alkayar
** Login   <WASSEX@epitech.net>
** 
** Started on  Fri Oct  6 22:53:25 2017 Wassim Alkayar
** Last update Sun Oct  8 12:32:22 2017 Wassim Alkayar
*/

#include "mysh.h"

char	*cut_alias(char *alias)
{
  int	i;
  int	j;
  char	*new;

  i = 1;
  j = 0;
  if ((new = malloc(sizeof(char) * my_strlen(alias))) == NULL)
    return (NULL);
  while (alias[i] != '\0' && alias[i - 1] != ' ')
    i++;
  i += 1;
  while (alias[i] != '\0' && alias[i - 1] != ' ')
    i++;
  while (alias[i] != '\0')
    {
      new[j] = alias[i];
      j += 1;
      i += 1;
    }
  new[j] = '\0';
  return (new);
}

void		print_aliases(t_dlist list)
{
  t_cell	*tmp;

  if (list == NULL || list->length == 0)
    return ;
  tmp = list->begin;
  while (tmp != NULL)
    {
      my_putstr(tmp->str);
      my_putstr("  ");
      my_putstr(tmp->str2);
      my_putchar('\n');
      tmp = tmp->next;
    }
}

t_dlist		new_or_not(t_shell *sh,
			   t_cell *tmp,
			   char *buffer)
{
  t_cell	*tmp2;

  tmp2 = NULL;
  if (sh->tmp_alias != NULL)
    tmp2 = sh->tmp_alias->begin;
  while (tmp2 != NULL)
    {
      if ((my_strcmp(tmp2->str, tmp->next->str)) == 0)
	break ;
      tmp2 = tmp2->next;
    }
  if (tmp2 == NULL)
    {
      sh->tmp_alias = push_back_dlist(sh->tmp_alias, tmp->next->str);
      sh->tmp_alias->end->str2 = cut_alias(buffer);
    }
  else
    tmp2->str2 = cut_alias(buffer);
  return (sh->tmp_alias);
}

t_dlist		put_tmp_alias(t_shell *sh, char *buffer)
{
  t_cell	*tmp;

  tmp = sh->buffer_list->begin;
  if (sh->buffer_list->length == 1 && ((my_strcmp(tmp->str, "alias")) == 0))
    {
      print_aliases(sh->tmp_alias);
      return (sh->tmp_alias);
    }
  if (sh->buffer_list->length > 1 &&
      ((my_strcmp(tmp->next->str, "alias")) == 0))
    {
      my_putstr("alias: Too dangerous to alias that.\n");
      sh->retvalue = 1;
      return (sh->tmp_alias);
    }
  else if (sh->buffer_list->length >= 3)
    {
      sh->tmp_alias = new_or_not(sh, tmp, buffer);
      sh->retvalue = 0;
    }
  return (sh->tmp_alias);
}

int		is_tmp_alias(t_shell *sh)
{
  t_cell	*tmp;

  if (sh->tmp_alias == NULL || sh->tmp_alias->length == 0)
    return (0);
  tmp = sh->tmp_alias->begin;
  while (tmp != NULL)
    {
      if ((my_strcmp(sh->buffer_list->begin->str, tmp->str)) == 0)
	break ;
      tmp = tmp->next;
    }
  if (tmp == NULL)
    return (0);
  sh->buffer_list = free_list(sh->buffer_list);
  sh->buffer_list = init_parsing(sh->buffer_list, tmp->str2);
  first_commands(sh);
  return (1);
}
