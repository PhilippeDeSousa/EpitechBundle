#include "minishell.h"

int should_exit(t_shell *shell, char *buffer) {
    if (find(buffer, "exit") == 0) {
        if (!is_nbr(cut_string(buffer, "exit"))) {
            my_putstr(2, EXIT_ERR);
            shell->exit_value = 1;
            return 1;
        } else {
            shell->exit_value = my_exit(shell, cut_string(buffer, "exit"));
            return (0);
        }
    }
    return 1;
}

int is_nbr(const char *str) {
    for (int i = 0; str[i]; i++) {
        if (str[i] < '0' || str[i] > '9')
            return (0);
    }
    return (1);
}

static void free_shell(t_shell *shell) {
    free_array(shell->env);
    free_array(shell->paths);
}

int my_exit(t_shell *shell, const char *val) {
    int return_val = 0;

    free_shell(shell);
    if (val == NULL || val[0] == '\0') {
        return (shell->exit_value);
    }
    if (!is_nbr(val)) {
        my_putstr(2, EXIT_ERR);
        return (-1);
    }
    return_val = convertnb(val);
    if (return_val > 255 || return_val < 0)
        return_val = 255;
    return (return_val);
}