/*
** shell_tools.c for  in /home/WASSEX/Semestre2/PSU/PSU_2016_42sh/src
** 
** Made by Wassim Alkayar
** Login   <WASSEX@epitech.net>
** 
** Started on  Thu Sep 28 17:11:41 2017 Wassim Alkayar
** Last update Fri Oct  6 22:47:39 2017 Wassim Alkayar
*/

#include <time.h>
#include "mysh.h"

t_dlist		history_upgrade(t_dlist history, char *buffer)
{
  time_t	hour;
  char		buff[20];

  if ((my_strcmp(buffer, "")) == 0)
    return (history);
  hour = time(NULL);
  strftime(buff, sizeof(buff), "%I:%M", localtime(&hour));
  history = push_back_dlist(history, buffer);
  history->end->time = my_strdup(buff);
  return (history);
}

t_dlist	buffer_from_parser(t_dlist buffer_list,
			   t_cell **tmp)
{
  while (*tmp != NULL)
    {
      if ((my_strcmp((**tmp).str, ";")) == 0 ||
	  (my_strcmp((**tmp).str, "&&")) == 0 ||
	  (my_strcmp((**tmp).str, "||")) == 0)
	{
	  if ((**tmp).next != NULL)
	    *tmp = (**tmp).next;
	  break ;
	}
      buffer_list = push_back_dlist(buffer_list, (**tmp).str);
      *tmp = (**tmp).next;
    }
  return (buffer_list);
}

int		separator_return_value(t_cell *mem, int *retvalue)
{
  int		ret;

  ret = 0;
  while (mem != NULL)
    {
      if ((my_strcmp(mem->str, ";")) == 0)
	ret = 1;
      else if ((my_strcmp(mem->str, "&&")) == 0)
	ret = 2;
      else if ((my_strcmp(mem->str, "||")) == 0)
	ret = 3;
      if (ret == 1 || ret == 2 || ret == 3)
	break ;
      mem = mem->next;
    }
  if (ret == 2 && *retvalue != 0)
    return (1);
  else if (ret == 3 && *retvalue == 0)
    return (1);
  return (0);
}
