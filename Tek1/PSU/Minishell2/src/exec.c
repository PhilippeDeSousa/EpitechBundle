#include "minishell.h"
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include "sys/types.h"
#include "sys/stat.h"

static int check_rights(const char *command) {
    struct stat st;
    DIR *dir;

    if ((dir = opendir(command))) {
        my_puterr(2, command, PERM_DENIED);
        free(dir);
        return 1;
    } else if (!(stat(command, &st) != 0 || st.st_mode & S_IXUSR)) {
        my_puterr(2, command, PERM_DENIED);
        return 1;
    }
    return 0;
}

static int print_sig(const int status) {
    switch (WTERMSIG(status)) {
        case SIGSEGV:
            my_putstr(2, SEGV);
            return (139);
        case SIGQUIT:
            my_putstr(2, QUIT);
            break;
        case SIGABRT:
            my_putstr(2, ABRT);
            break;
        case SIGBUS:
            my_putstr(2, BUS);
            break;
        case SIGFPE:
            my_putstr(2, FPE);
            return (136);
        default:
            break;
    }
    return (0);
}

int exec_everywhere(t_shell *shell, char **av, const char *command) {
    char **paths = shell->paths;
    char *full_command;

    if (paths == NULL)
        return (-1);
    if (execve(command, av, shell->env) != - 1)
        return (0);
    if (errno == ENOEXEC) {
        my_puterr(2, command, BIN_ERROR);
        return (0);
    }
    for (size_t i = 0; paths[i]; i++) {
        full_command = my_strcat(paths[i], command);
        if (execve(full_command, av, shell->env) != - 1) {
            free_array(paths);
            return (0);
        }
        free(full_command);
    }
    free_array(paths);
    return (-1);
}

static int exec(t_shell *shell, const char *command) {
    char **args;
    int ex_val = 0;

    args = str_to_array(command, ' ');
    if ((ex_val = exec_everywhere(shell, args, args[0])) == -1) {
        if (!check_rights(command)) {
            my_puterr(2, command, CMD_NOT_FOUND);
        }
        free_array(args);
        exit(1);
    }
    exit(0);
}

int exec_command(t_shell *shell, const char *command) {
    pid_t pid;
    int status;

    if ((pid = fork()) == -1) {
        my_putstr(2, "Fork failed.\n");
        return (-1);
    } else if (pid == 0) {
        exec(shell, command);
    } else {
        waitpid(pid, &status, 0);
        if (WIFSIGNALED(status))
            return (print_sig(status));
        if (status != 0)
            return (1);
    }
    return (0);
}