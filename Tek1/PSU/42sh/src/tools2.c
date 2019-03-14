/*
** tools2.c for  in /home/WASSEX/Semestre1/PSU/PSU_2016_minishell1/src
** 
** Made by Wassim Alkayar
** Login   <WASSEX@epitech.net>
** 
** Started on  Sat Jun 17 21:49:44 2017 Wassim Alkayar
** Last update Sun Oct  8 01:54:26 2017 Wassim Alkayar
*/

#include <stdio.h>
#include <signal.h>
#include "mysh.h"

void	my_putchar_err(char c)
{
  write(2, &c, 1);
}

void	my_putstr_err(char *str)
{
  int	i;

  if (str == NULL)
    return ;
  i = 0;
  while (str[i] != '\0')
    {
      my_putchar_err(str[i]);
      i += 1;
    }
}

int	convertnb(char *str)
{
  int	i;
  int	result;
  int	sign;

  i = 0;
  result = 0;
  sign = 1;
  if (str == NULL)
    return (0);
  if (str[0] == '-')
    {
      sign = -1;
      i = i + 1;
    }
  while (str[i] != '\0')
    {
      result = result * 10 + str[i] - '0';
      i = i + 1;
    }
  return (sign * result);
}

int	print_errors(int status)
{
  if (WTERMSIG(status) == SIGSEGV)
    {
      my_putstr_err(SEG);
      return (139);
    }
  else if (WTERMSIG(status) == SIGQUIT)
    my_putstr_err(QUIT);
  else if (WTERMSIG(status) == SIGABRT)
    my_putstr_err(ABRT);
  else if (WTERMSIG(status) == SIGBUS)
    my_putstr_err(BUS);
  else if (WTERMSIG(status) == SIGFPE)
    {
      my_putstr_err(FPE);
      return (136);
    }
  return (0);
}

char	*add_equal_sign(char *str)
{
  int	i;
  char	*replace;

  i = 0;
  if ((replace = malloc(sizeof(char) * (my_strlen(str) + 2))) == NULL)
    return (NULL);
  while (str[i] != '\0')
    {
      replace[i] = str[i];
      i += 1;
    }
  replace[i] = '=';
  replace[i + 1] = '\0';
  return (replace);
}
