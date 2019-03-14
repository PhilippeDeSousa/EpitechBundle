/*
** execute_alias.c for  in /home/WASSEX/Semestre2/PSU/PSU_2016_42sh
** 
** Made by Wassim Alkayar
** Login   <WASSEX@epitech.net>
** 
** Started on  Sun Oct  1 14:26:13 2017 Wassim Alkayar
** Last update Mon Oct  2 17:55:18 2017 Wassim Alkayar
*/

#include "mysh.h"

void		execute_alias(char *command, t_shell *sh, char *buffer)
{
  t_cell	*tmp;

  sh->buffer_list = free_list(sh->buffer_list);
  sh->parser_list = free_list(sh->parser_list);
  sh->parser_list = init_parsing(sh->parser_list, command);
  tmp = sh->parser_list == NULL ? NULL : sh->parser_list->begin;
  if (tmp == NULL)
    {
      sh->retvalue = 1;
      my_putstr(buffer);
      my_putstr(CMD_NOT_FOUND);
    }
  while (tmp != NULL)
    {
      if (execute_part(&tmp, sh, NULL) == 1)
	return ;
    }
}
