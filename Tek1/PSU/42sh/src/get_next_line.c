/*
** get_next_line.c for  in /home/WASSEX/Semestre1/CPE/CPE_2016_getnextline
** 
** Made by Wassim Alkayar
** Login   <WASSEX@epitech.net>
** 
** Started on  Thu May 25 15:31:45 2017 Wassim Alkayar
** Last update Thu Aug 31 19:52:07 2017 Wassim Alkayar
*/

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "mysh.h"

char	*add_mem(char *str)
{
  char	*replace;
  int	i;
  int	mallocsize;

  i = 0;
  mallocsize = my_strlen(str) + 2;
  replace = malloc(sizeof(char) * mallocsize);
  if (replace == NULL)
    return (NULL);
  while (str[i] != '\0')
    {
      replace[i] = str[i];
      i += 1;
    }
  replace[i + 1] = '\0';
  free(str);
  return (replace);
}

char		get_act_char(const int fd)
{
  static char	buff[READ_SIZE];
  static char	*ptr;
  static int	ct = 0;
  char		act_char;

  if (ct == 0)
    {
      ct = read(fd, buff, READ_SIZE);
      if (ct == 0)
	return (0);
      ptr = buff;
    }
  act_char = *ptr;
  ptr = ptr + 1;
  ct = ct - 1;
  return (act_char);
}

char		*get_next_line(const int fd, char c)
{
  int		i;
  char		act_char;
  char		*str;

  i = 0;
  if ((str = malloc(sizeof(char) * 2)) == NULL)
    return (NULL);
  str[1] = '\0';
  act_char = get_act_char(fd);
  while (act_char != c)
    {
      if (act_char == '\0')
	return (NULL);
      str[i] = act_char;
      str = add_mem(str);
      act_char = get_act_char(fd);
      i += 1;
      if (act_char == '\0')
	{
	  str[i] = '\0';
	  return (str);
	}
    }
  str[i] = '\0';
  return (str);
}
