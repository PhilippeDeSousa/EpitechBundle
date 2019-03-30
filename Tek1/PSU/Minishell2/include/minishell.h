#ifndef MINISHELL_H_
# define MINISHELL_H_

#include "stdbool.h"
#include "stdio.h"
#include "unistd.h"
#include "get_next_line.h"
#include <sys/types.h>
#include <sys/wait.h>

#define FLAG (1)
#define COMMAND (2)

#define CMD_NOT_FOUND ": Command not found.\n"
#define BIN_ERROR ": Exec format error. Binary file not executable.\n"
#define PERM_DENIED ": Permission denied.\n"
#define EXIT_ERR "exit: Expression Syntax.\n"
#define NOT_DIR ": Not a directory.\n"
#define NO_SUCH_FILE ": No such file or directory.\n"
#define HOMEDIR_ERR ": Can't change to home directory.\n"
#define SETENV_ERR "setenv: Too many arguments.\n"
#define SEGV "Segmentation fault (core dumped)\n"
#define QUIT "Quit (core dumped)\n"
#define	ABRT "Abort (core dumped)\n"
#define	BUS "Bus error (core dumped)\n"
#define	FPE "Floating exception\n"

typedef struct s_tree {
    char        *command;
    struct s_tree *left;
    struct s_tree *right;

}           t_tree;

typedef struct  s_command {
    int         type;
    char        *content;
}               t_command;

typedef struct  s_shell {
    char        ***free_commands;
    char        **env;
    char        **paths;
    t_tree      *commands;
    int         exit_value;
    int         should_exit;
}               t_shell;

typedef struct			s_flag
{
  char				*code;
  int				(*fc)(t_shell *);
}				        t_flag;

        /* shell.c */

int shell(const char * const *);

        /* lib */

void my_putstr(const int, const char *);
void my_puterr(const int, const char *, const char*);
void print_array(char **);
void free_array(char **);

int my_strcmp(const char *, const char *);
int find(const char *, const char *);
int convertnb(const char *);
int is_nbr(const char *);

size_t arr_len(char **);
size_t my_strlen(const char *);

char *my_strdup(const char *);
char *add_equal(const char *);
char *cut_string(char *, const char *);
char *my_strncpy(char *, const char*, size_t, size_t);
char *epur_str(char *);
char *my_strcat(const char*, const char*);
char *form_directory(const char *, const char *);

char **str_to_array(const char *, char);

        /* builtins */

int my_setenv(char ***, char *);
int my_unsetenv(char ***, char *);
int my_exit(t_shell *, const char *);
int should_exit(t_shell *, char *);
int my_cd(char ***, const char *);

char *return_home(char **);

        /* src */

int exec_command(t_shell *, const char *);
int right_chevron(t_shell *);

void interpretor(t_shell *, char *);
void parse_tree(t_shell *, t_tree *);
char **parse_env(const char *, char);
char **get_all_paths(char **);
char **set_commands(const char *);
char **command_launcher(t_shell *, char *);

void parse_input(t_shell *, const char *);

void print_tree(t_tree *);
void create_tree(char **, t_tree *);

        /* flags */

int handle_sup(t_shell *, char *, char *, t_tree *);
int handle_pipe(t_shell *, char *, char *);


#endif /* MINISHELL_H */