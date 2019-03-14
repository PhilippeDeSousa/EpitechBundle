/*
** main.c for  in /home/WASSEX/Semestre1/PSU/PSU_2016_minishell1
** 
** Made by Wassim Alkayar
** Login   <WASSEX@epitech.net>
** 
** Started on  Mon Jun 12 15:22:27 2017 Wassim Alkayar
** Last update Sun Oct  8 18:42:08 2017 Wassim Alkayar
*/

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <signal.h>
#include "mysh.h"

void	ctrl_c(int a)
{
  a += 0;
  my_putchar('\n');
}

int		main(int argc, char **argv, char **env)
{
  t_shell	shell;
  char		*buffer;
  int		isat;

  isat = 0;
  if (env[0] == NULL)
    isat = 1;
  if (argc != 1 && ((my_strcmp(argv[0], "./mysh")) == 0))
    {
      my_putstr_err(ARGC_ERR);
      return (84);
    }
  buffer = NULL;
  signal(SIGINT, ctrl_c);
  shell.retvalue = 0;
  shell.envlist = NULL;
  shell.buffer_list = NULL;
  shell.envlist = create_env_dlist(shell.envlist, env, isat);
  minishell(buffer, &shell);
  shell.envlist = free_list(shell.envlist);
  return (shell.retvalue);
}
