#include "minishell.h"

char **command_launcher(t_shell *shell, char *buffer);

int create_file(char *file, int *fd) {
    int flags = O_CREAT | O_RDWR | O_TRUNC;

    *fd = open(file, flags, 0644);
    if (*fd == -1) {
        my_puterr(2, file, ": couldn't create or open.\n");
        return (84);
    }
    return (0);
}

int handle_sup(t_shell *shell, char *command1, char *command2, t_tree *tree) {
    int pid;
    int status;
    int fd;

    if (create_file(command2, &fd) == 84)
        return (84);
    if ((pid  = fork())== -1)
        return (84);
    else if (pid == 0) {
        dup2(fd, 1);
        if (tree->left)
            parse_tree(shell, tree);
        else
            command_launcher(shell, command1);
        close(fd);
        exit(shell->exit_value);
    }
    else {
        waitpid(pid, &status, 0);
        shell->exit_value = status;
    }
    return (0);
}