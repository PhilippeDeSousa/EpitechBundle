/*
** main.c for main in /home/Max/Documents
** 
** Made by fourrier maxence
** Login   <maxence.fourrier@epitech.eu>
** 
** Started on  Tue Apr 25 13:13:22 2017 fourrier maxence
** Last update Sat Sep 23 19:08:45 2017 Wassim Alkayar
*/

#include "my.h"
#include "get_next_line.h"

int	main(int argc, char **argv)
{
  char	*buff;

  (void)(argv);
  if (argc > 1)
    {
      my_putstr("Usage : ./lem_in < [file]\n");
      return (SUCCESS);
    }
  if ((buff = get_next_line(0, '\0')) == NULL)
    return (ERROR);
  if ((my_strlen(buff)) == 0)
    {
      my_putstr("Invalid file size\n");
      return (ERROR);
    }
  if ((buff = check_buff(buff)) == NULL
      || lemin(buff) == ERROR)
    return (ERROR);
  return (SUCCESS);
}
