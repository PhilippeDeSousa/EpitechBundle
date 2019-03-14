/*
** tools.c for  in /home/WASSEX/Semestre1/PSU/PSU_2016_minishell1/src
** 
** Made by Wassim Alkayar
** Login   <WASSEX@epitech.net>
** 
** Started on  Wed Jun 14 04:32:25 2017 Wassim Alkayar
** Last update Thu Sep 28 18:03:31 2017 Wassim Alkayar
*/

#include "mysh.h"

char	*link_strings(char *str1, char *str2)
{
  int	i;
  int	j;
  char	*replace;

  i = 0;
  replace = NULL;
  if ((replace = malloc(sizeof(char) * (my_strlen(str1) +
					my_strlen(str2) + 1))) == NULL)
    return (NULL);
  while (str1[i] != '\0')
    {
      replace[i] = str1[i];
      i += 1;
    }
  j = 0;
  while (str2[j] != '\0')
    {
      replace[i] = str2[j];
      i += 1;
      j += 1;
    }
  replace[i] = '\0';
  return (replace);
}

void	put_path_name(char *pathmem)
{
  my_putstr(CH_DIR);
  my_putstr(pathmem);
  my_putchar('\n');
}

char	*clear_buffer(char *buffer)
{
  int	i;

  i = 0;
  while (buffer[i] != '\0')
    {
      buffer[i] = '\0';
      i += 1;
    }
  return (buffer);
}

t_dlist		free_list(t_dlist buffer_list)
{
  t_cell	*tmp;
  t_cell	*del;
  t_dlist	replace;

  if (buffer_list == NULL)
    return (NULL);
  if (buffer_list->length == 0)
    return (0);
  replace = NULL;
  tmp = buffer_list->begin;
  while (tmp != NULL)
    {
      del = tmp;
      tmp = tmp->next;
      free(del);
      del = NULL;
    }
  return (replace);
}

char		**list_to_tab(t_dlist buffer_list)
{
  char		**tab;
  int		i;
  t_cell	*tmp;
  int		malloc_size;

  malloc_size = buffer_list->length + 1;
  if ((tab = malloc(sizeof(char *) * malloc_size)) == NULL)
    return (NULL);
  i = 0;
  tmp = buffer_list->begin;
  while (tmp != NULL)
    {
      tab[i] = my_strdup(tmp->str);
      i += 1;
      tmp = tmp->next;
    }
  tab[i] = NULL;
  return (tab);
}
