/*
** shell.c for  in /home/WASSEX/Semestre2/PSU/PSU_2016_minishell2/src
** 
** Made by Wassim Alkayar
** Login   <WASSEX@epitech.net>
** 
** Started on  Thu Aug 17 18:38:33 2017 Wassim Alkayar
** Last update Sun Oct  8 18:46:48 2017 Wassim Alkayar
*/

#include "mysh.h"

void		commands(t_dlist buffer_list,
			 t_dlist envlist,
			 int *retvalue)
{
  t_dlist	pathlist;

  pathlist = NULL;
  pathlist = get_all_path_bin(envlist);
  if (check_cd(buffer_list) == 6)
    change_directory(buffer_list, &envlist, buffer_list->length, retvalue);
  else if ((check_env(buffer_list)) == 3)
    env(envlist);
  else if ((check_setenv(buffer_list, envlist, retvalue)) == 4)
    my_setenv(buffer_list, &envlist, buffer_list->length, retvalue);
  else if ((check_unsetenv(buffer_list, retvalue)) == 5)
    prepare_unsetenv(envlist, buffer_list);
  else
    binary_exec(buffer_list->begin->str, list_to_tab(buffer_list),
		envlist, retvalue);
  pathlist = free_list(pathlist);
}

void	first_commands(t_shell *sh)
{
  if ((check_and_execute_history(sh)) == 1)
    return ;
  else if ((my_strcmp(sh->buffer_list->begin->str, "repeat")) == 0)
    repeat(sh);
  else if ((check_pipe(sh) == 0))
    return ;
  else if ((check_right_redirections(sh->buffer_list)) == 11)
    right_redirections(sh->buffer_list, sh->envlist, &sh->retvalue);
  else if ((check_left_redirections(sh->buffer_list)) == 12)
    left_redirections(sh->buffer_list, sh->envlist, &sh->retvalue);
  else if ((check_globbing(sh)) == 1)
    execute_globbing(sh);
  else
    commands(sh->buffer_list, sh->envlist, &sh->retvalue);
}

int		execute_part(t_cell **tmp, t_shell *sh, char *buffer)

{
  int		ret;
  t_cell	*mem;

  ret = sh->retvalue;
  mem = (**tmp).back;
  if ((sh->buffer_list = buffer_from_parser(sh->buffer_list, tmp)) != NULL &&
      (separator_return_value(mem, &sh->retvalue) == 0))
    {
      if ((is_exit(sh->buffer_list, &ret)) == 50)
	return (1);
      else if ((my_strcmp(sh->buffer_list->begin->str, "alias")) == 0)
	sh->tmp_alias = put_tmp_alias(sh, buffer);
      else if ((is_tmp_alias(sh)) == 1)
	ret = ret;
      else
	first_commands(sh);
    }
  sh->buffer_list = free_list(sh->buffer_list);
  return (0);
}

void		minishell(char *buffer, t_shell *shell)
{
  t_cell	*tmp;

  shell->parser_list = NULL;
  shell->history = NULL;
  shell->tmp_alias = NULL;
  my_putstr(">");
  while ((buffer = get_next_line(0, '\n')) != NULL)
    {
      shell->history = history_upgrade(shell->history, buffer);
      shell->parser_list = init_parsing(shell->parser_list, buffer);
      tmp = shell->parser_list == NULL ? NULL : shell->parser_list->begin;
      while (tmp != NULL)
	if (execute_part(&tmp, shell, buffer) == 1)
	  return ;
      shell->parser_list = free_list(shell->parser_list);
      my_putstr(">");
    }
}
