#ifndef MINISHELL_H_
# define MINISHELL_H_

#include "stdbool.h"
#include "stdio.h"
#include "unistd.h"
#include "get_next_line.h"
#include <sys/types.h>
#include <sys/wait.h>

#define CMD_NOT_FOUND ": Command not found.\n"
#define BIN_ERROR "Exec format error. Binary file not executable.\n"
#define PERM_DENIED ": Permission denied.\n"
#define EXIT_ERR "exit: Expression Syntax.\n"
#define NOT_DIR ": Not a directory.\n"
#define NO_SUCH_FILE ": No such file or directory.\n"
#define HOMEDIR_ERR ": Can't change to home directory.\n"
#define SETENV_ERR "setenv: Too many arguments.\n"
#define SEGV "Segmentation fault (core dumped)\n"
#define QUIT "Quit (core dumped)\n"
#define	ABRT "Abort (core dumped)\n"
#define	BUS	"Bus error (core dumped)\n"
#define	FPE	"Floating exception\n"

typedef struct  s_shell {
    char        **env;
    char        **paths;
    char        **commands;
    int         exit_value;
    int         should_exit;
}               t_shell;
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

void interpretor(t_shell *, char *);
char **parse_env(const char *, char);
char **get_all_paths(char **);
char **parse_input(const char *);


#endif /* MINISHELL_H */