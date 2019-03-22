/*
** my.h for  in /home/WASSEX/Semestre2/CPE/test/CPE_2016_Lemin
** 
** Made by Wassim Alkayar
** Login   <WASSEX@epitech.net>
** 
** Started on  Thu Sep 21 16:41:12 2017 Wassim Alkayar
** Last update Mon Sep 25 17:13:51 2017 Wassim Alkayar
*/

#ifndef MY_H_
# define MY_H_

/*      __________ ________________________ __________
**
**                        INCLUDES
**      __________ ________________________ __________
*/

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

/*      __________ ________________________ __________
**
**                        DEFINES
**      __________ ________________________ __________
*/

/*
**		     __ Succes Messages __
*/

# define NOA		"#number_of_ants\n"

# define START		"##start\n"

# define TUNNELS	"#tunnels\n"

# define ROOMS		"#rooms\n"

# define MOVES		"#moves\n"

/*
**		     __ Error Message __
*/

# define OPEN_MSG	"Open Error.\n"

# define READ_MSG	"Read Error.\n"

# define MALLOC_MSG	"Malloc Error.\n"

/*
**	             __ Returns Values __
*/

# define SUCCESS	0
# define ERROR		84

/*      __________ ________________________ __________
**
**                       STRUCTURES
**      __________ ________________________ __________
*/

typedef struct		s_ptr
{
  char			*str;
  void			(*fnc)();
}			t_ptr;

typedef struct		s_road
{
  char			*a;
  char			*b;
}			t_road;

typedef struct		s_room
{
  char			*room;
  int			x;
  int			y;
}			t_room;

typedef struct		s_print
{
  int			room;
  int			tunnel;
  int			start;
  int			end;
  int			sp;
}			t_print;

typedef struct		s_path
{
  char			*first;
  char			*last;
}			t_path;

typedef struct		s_fin
{
  char			**tab;
  char			**full;
  char			**max;
}			t_fin;

typedef struct		s_nb
{
  int			nb_roads;
  int			nb_ants;
  char			*beg;
  char			*end;
}			t_nb;

typedef struct		s_ant
{
  int			a;
}			t_ant;

typedef struct		s_cell
{
  char			*a;
  char			*b;
  char			*room;
  struct s_cell		*next;
  struct s_cell		*back;
}			t_cell;

struct			s_dlist
{
  int			length;
  t_cell		*begin;
  t_cell		*end;
};

typedef struct s_dlist	*t_dlist;

char	*my_strdup(char *);
t_dlist	get_all_roads(t_road **, char *, char *);
t_dlist	push_back_dlist(t_dlist, char *, char *);
void	print_dlist(t_dlist);
t_dlist	free_list(t_dlist, int);
t_dlist	list_to_list(t_dlist, t_dlist);
char	*convertstr(int);
char	**str_to_tab(char *);
char	*get_start(char **);
char	*get_end(char **);
char	*first_nb(char *);
int	is_end(char *, int);
int	number_of_ants(char *);
int	start_end(char **);
t_dlist	get_begin_roads(t_dlist, t_road **, char *);
int	is_continue(char *, t_road **);
t_dlist	get_new_room(t_dlist, char *, t_road **);
t_road	**epur_road(t_road **);

/*      __________ ________________________ __________
**
**                        LEMIN
**      __________ ________________________ __________
*/

/*
**	             __ utils.c __
*/
int		get_x_room(char *);

/*
**	             __ init_room.c __
*/
int		is_room(char *);
t_room		*my_link_room(char *);
int		nb_room(char *);
t_room		**init_room(char *);

/*
**	             __ init_road.c __
*/
int		is_road(char *);
t_road		*my_link_road(char *);
int		nb_road(char *);
t_road		**init_road(char *);

/*
**	             __ del_space.c __
*/
char		*del_space(char *);

/*
**	             __ del_comment.c __
*/
char		*del_comment(char *);

/*
**	             __ del_back.c __
*/
char		*del_line_in(char *, char *, int *, int *);
char		*del_line(char *);

/*
**	             __ check_buff.c __
*/
char		*check_buff();

/*
**	             __ get_buff.c __
*/
int		get_size();
char		*get_buff();

/*
**	             __ tools.c __
*/
char		*get_line(char **);
int		is_number(char *);
int		is_letter(char);
int		is_num(char);

/*
**	             __ lemin.c __
*/
int		print_lemin(char **);
t_fin		get_all_path(t_road**, t_nb);
void		init_val(int*, int*, int*);
int		lemin(char *);
/*
**	             __ get_all_path.c __
*/

int		tab_size(t_road**);
char		*my_strcat(char*, char*);
t_fin		rm_dup(t_fin, char*, int);

/*
**	             __ getpos.c __
*/

int		get_road(char*, char*, t_road**);

/*
**	             __ moves.c __
*/

void		moves(char**, t_nb);
int		convertnb(char*);
/*      __________ ________________________ __________
**
**                         LIBRARY
**      __________ ________________________ __________
*/

int	my_decimal_to_octal(int nb);
int	my_strlen(char *str);
int	my_str_who_bigger(char *s1, char *s2);
int	my_str_to_int(char *str);
int	my_strcmp(char *a, char *b);
int	my_swap(int *a, int *b);

void	my_putstr_error(char *str);
void	my_putnbr(int nb);
void	my_putchar(char a);
void	my_putstr(char *str);

char	*my_int_to_str(int nb);
char	*my_str_maj(char *str);
char	*my_decimal_to_hexa(int nb);
char	*supp_0(char *str);
char	*my_revstr(char *str);
char	*my_strcpy(char *dest, char *src);

#endif /* !_MY_H_ */
