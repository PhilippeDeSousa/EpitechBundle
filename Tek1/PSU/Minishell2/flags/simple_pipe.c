#include "minishell.h"

int simple_pipe(t_shell *shell, char *command1, char *command2) {
    int pfd[2];
    int pid;

    if (pipe(pfd) == -1)
        return (84);
    if ((pid = fork()) == -1)
        return (84);
    if (pid == 0) {
        close(pfd[1]);
        dup2(pfd[0], 0);
        close(pfd[0]);
        shell->env = command_launcher(shell, command2);
        exit(shell->exit_value);
    }
    else {
        close(pfd[0]);
        dup2(pfd[1], 1);
        close(pfd[1]);
        shell->env = command_launcher(shell, command1);
        exit(shell->exit_value);
    }
    return (0);
}

int handle_pipe(t_shell *shell, char *command1, char *command2) {
    int status = 0;
    int pid = fork();

    if (pid == -1)
        return (84);
    pid == 0 ? simple_pipe(shell, command1, command2) : waitpid(pid, &status, 0);
    shell->exit_value = status > 1 ? 1 : 0;
    return (0);
}