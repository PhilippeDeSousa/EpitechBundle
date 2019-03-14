/*
** parsing.c for  in /home/WASSEX/Semestre2/PSU/PSU_2016_minishell2
** 
** Made by Wassim Alkayar
** Login   <WASSEX@epitech.net>
** 
** Started on  Mon Aug 21 17:23:52 2017 Wassim Alkayar
** Last update Fri Oct  6 22:46:19 2017 Wassim Alkayar
*/

#include "mysh.h"

t_dlist		manage_list(t_dlist buffer_list, char *occ, int *i, int add)
{
  buffer_list = push_back_dlist(buffer_list, occ);
  *i += add;
  return (buffer_list);
}

t_dlist		parsing_conditions(t_dlist buffer_list,
				   char *occ,
				   char *buffer,
				   int *i)
{
  if (my_strcmp(occ, "") != 0 && my_strcmp(occ, "\t") != 0)
    buffer_list = manage_list(buffer_list, occ, i, 0);
  if (*i >= 1 && buffer[*i] == ';')
    buffer_list = manage_list(buffer_list, ";", i, 1);
  else if (*i >= 1 && buffer[*i] == '&' && buffer[*i + 1] == '&')
    buffer_list = manage_list(buffer_list, "&&", i, 2);
  else if (*i >= 1 && buffer[*i] == '|' && buffer[*i + 1] == '|')
    buffer_list = manage_list(buffer_list, "||", i, 2);
  else if (buffer[*i] == '|')
    buffer_list = manage_list(buffer_list, "|", i, 1);
  else
    *i += 1;
  return (buffer_list);
}

t_dlist		buffer_to_list(t_dlist buffer_list, char *buffer, int i, int j)
{
  char		*occ;

  while (buffer != NULL && buffer[i] != '\0')
    {
      if ((occ = malloc(sizeof(char) * (my_strlen(buffer) + 1))) == NULL)
	return (0);
      j = 0;
      while (buffer[i] != '\0')
	{
	  if (buffer[i] == ' ' || buffer[i] == '\t' || buffer[i] == ';' ||
	      buffer[i] == '|' || buffer[i] == '&')
	    break ;
	  occ[j++] = buffer[i++];
	}
      occ[j] = '\0';
      buffer_list = parsing_conditions(buffer_list, occ, buffer, &i);
    }
  return (buffer_list);
}

t_dlist		init_parsing(t_dlist buffer_list, char *buffer)
{
  int		i;
  int		j;

  i = 0;
  j = 0;
  buffer_list = buffer_to_list(buffer_list, buffer, i, j);
  return (buffer_list);
}
