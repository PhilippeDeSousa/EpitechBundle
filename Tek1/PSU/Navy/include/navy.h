/*
** navy.h for  in /home/WASSEX/Semestre2/PSU_2016_navy
** 
** Made by Wassim Alkayar
** Login   <WASSEX@epitech.net>
** 
** Started on  Tue Jun 27 21:47:15 2017 Wassim Alkayar
** Last update Thu Jul 13 20:49:54 2017 Wassim Alkayar
*/

#ifndef NAVY_H_
# define NAVY_H_

# ifndef READ_SIZE
#  define READ_SIZE (2)
# endif /* !READ_SIZE */

# include <sys/types.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>

# define MAP_SIZE		180
# define READ_SIZE_2		200
# define MAP_LINE_LENGTH	20
# define POS_LINE_LENGTH	8
# define MARGIN			2
# define WAIT			100
# define MAP_FORMAT_LOCATION	"src/map_format"
# define WAIT_CONNECTION	"waiting for enemy connexion...\n"
# define WAIT_ATTACK		"waiting for enemy's attack...\n"
# define WIN			"I won\n"
# define LOOSE			"Enemy won\n"
# define FAIL_SIGNAL_HANDLE	"Failed to handle signal\n"
# define FAIL_SIGNAL_SEND	"Failed to send signal\n"
# define FAIL_USLEEP		"Failed to usleep\n"
# define CONNECTED		"successfully connected\n\n"
# define ENEMY_CONNECTED	"enemy connected\n\n"

typedef struct	s_player
{
  int		player;
  int		attack_x;
  int		attack_y;
}		t_player;

struct		s_sig
{
  int		enemy_pid;
  int		signo;
}		sig;

typedef struct		s_vector
{
  int			x;
  int			y;
}			t_vector;

typedef struct		s_game
{
  int			hitnb;
  int			enemyhitnb;
  int			hitcheck;
  t_player		playerattak;
  t_player		enemyattak;
  char			**playerboard;
  char			**ennemyboard;
}			t_game;

char	*get_pos(char *, int);
char	**prepare_print_boats(char **, char *);
char	**map_to_tab();
char	*get_next_line(int);
int	my_strlen(char *);
void	my_putchar(char);
void	my_putstr(char *);
int	my_strcmp(char *, char *);
char	*read_pos(char *);
void	navy_man();
void	print_double_tab(char **tab);
int	start_game(char **, int);
int	convertnb(char *);
char	**prepare_game(char *);
int	connect(char **, t_player *);
void	my_put_nbr(int);
int	check_the_map(char *);
int	send_attack(int, int);
int	send_signal(int);
int	get_num(t_player *);
int	send_hit_or_miss(t_game *);
int	get_hit_or_miss();
int	new_x(char *, char **);
int	new_y(char *, char **);
int	is_move_ok(char *);
void	p1_complete_enemy_tab(t_game *, char *);
void	read_buffer(char *move[2]);
void	print_players_pos(t_game *);
void	init_game(t_game *, char **);
void	print_attack(t_game *);
void	print_hit_or_miss(t_game *);

#endif /* !NAVY_H_ */
