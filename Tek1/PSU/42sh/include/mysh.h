/*
** mysh.h for  in /home/WASSEX/Semestre1/PSU/PSU_2016_minishell1/include
** 
** Made by Wassim Alkayar
** Login   <WASSEX@epitech.net>
** 
** Started on  Mon Jun 12 15:06:52 2017 Wassim Alkayar
** Last update Sun Oct  8 18:46:08 2017 Wassim Alkayar
*/

#ifndef MYSH_H_
# define MYSH_H_

# include <stdlib.h>
# include <unistd.h>

# define	ARGC_ERR	"Usage : ./mysh\n"
# define	PROMPT		"→"
# define	UNFOUND_FILE	": No such file or directory.\n"
# define	SETENV_ERR	"setenv: Too many arguments.\n"
# define	SETENV_ERR_2	"setenv: Variable name must begin with a letter.\n"
# define SE3  "setenv: Variable name must contain alphanumeric characters.\n"
# define	UNSETENV_ERR	"unsetenv: Too few arguments.\n"
# define	CD_ERR		"Usage : cd [filename].\n"
# define	CD_ERR2		": Not a directory.\n"
# define	CD_ERR3		": No such file or directory.\n"
# define	EXIT_ERR	"exit: Expression Syntax.\n"
# define	CH_DIR		"Directory: "
# define	CMD_NOT_FOUND	": Command not found.\n"
# define	SEG		"Segmentation fault\n"
# define	QUIT		"Quit (core dumped)\n"
# define	ABRT		"Abort (core dumped)\n"
# define	BUS		"Bus error (core dumped)\n"
# define	FPE		"Floating exception\n"
# define	KILL		"Killed\n"
# define	SR1		"User signal 1\n"
# define	SR2		"User signal 2\n"
# define	NO_PERMISSION	": Permission denied.\n"
# define	BIN		"Exec format error. Binary file not executable.\n"
# define	PIPE_FILE	"first_file"
# define	PIPE_FILE2	"first_file2"
# define	PATH		"PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/heimdal/bin:"
# define	PATH_2		"/usr/heimdal/sbin:/home/WASSEX/bin"
# define	INV_NULL	"Invalid null command.\n"

typedef struct		s_cell
{
  char			*str;
  char			*str2;
  char			*time;
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

typedef struct		s_shell
{
  t_dlist		buffer_list;
  t_dlist		parser_list;
  t_dlist		tmp_alias;
  t_dlist		history;
  t_dlist		envlist;
  int			retvalue;
}			t_shell;

t_dlist	push_back_dlist(t_dlist, char *);
int	is_empty_dlist(t_dlist);
t_dlist	create_env_dlist(t_dlist, char **, int);
void	print_dlist(t_dlist);

void	my_putchar(char);
void	my_putstr(char *);
void	my_putstr_err(char *);
int	my_strlen(char *);
int	my_strcmp(char *, char *);
char	*my_strdup(char *);
char	*cut_str(char *);
int	convertnb(char *);
char	*my_strcat(char *, char *);
void	my_put_nbr(int);
char	**str_to_wordtab(char *);

char	*link_strings(char *, char *);
char	*add_equal_sign(char *);
t_dlist	init_parsing(t_dlist, char *);
t_dlist	free_list(t_dlist);
void	put_path_name(char *);
char	**list_to_tab(t_dlist);
int	print_errors(int);
int	check_non_alpha(char *);

void	minishell(char *, t_shell *);
void	first_commands(t_shell *);
void	commands(t_dlist, t_dlist, int *);
int	execute_part(t_cell **, t_shell *, char *);

int	separator_return_value(t_cell *, int *);
t_dlist	buffer_from_parser(t_dlist, t_cell **);
t_dlist	history_upgrade(t_dlist, char *);

void	binary_exec(char *, char **, t_dlist, int *);
t_dlist	get_all_path_bin(t_dlist);

void	change_directory(t_dlist, t_dlist *, int, int *);
void	update_path(char *, t_dlist *, char *);
char	*cut_path(char *);
char	*get_home_path(t_dlist *);

char	*get_next_line(const int, char);
char	*clear_buffer(char *);

int	check_cd(t_dlist);
int	check_exit(t_dlist, int);
int	is_exit(t_dlist, int *);
int	check_env(t_dlist);
int	check_setenv(t_dlist, t_dlist, int *);
int	check_unsetenv(t_dlist, int *);
int	check_and_execute_history(t_shell *);

void	env(t_dlist);
void	my_setenv(t_dlist, t_dlist *, int, int *);
void	prepare_unsetenv(t_dlist, t_dlist);
void	my_unsetenv(char *, t_dlist *);

int	check_right_redirections(t_dlist);
int	right_redirections(t_dlist, t_dlist, int *);
int	check_left_redirections(t_dlist);
int	left_redirections(t_dlist, t_dlist, int *);

int	check_pipe(t_shell *);
void	prepare_pipe(t_dlist, t_dlist, int *);
void	prepare_multiple_pipe(t_dlist, t_dlist, int *);
void	prepare_simple_pipe(t_dlist, t_dlist, int *);

char	*my_alias(char *);
void	execute_alias(char *, t_shell *, char *);
int	check_tmp_alias(t_shell *);
t_dlist	put_tmp_alias(t_shell *, char *);
void	print_aliases(t_dlist);
int	is_tmp_alias(t_shell *);

int	check_globbing(t_shell *);
void	execute_globbing(t_shell *);

void	repeat(t_shell *);
void	execute_repeat(t_shell *);

#endif /* !MYSH_H_ */
