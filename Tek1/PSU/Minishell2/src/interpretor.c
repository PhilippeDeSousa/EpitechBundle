#include "minishell.h"

static char **command_launcher(t_shell *shell, char *buffer) {
    if (should_exit(shell, buffer) == 0) {
        shell->should_exit = 1;
        return (shell->env);
    }
    if (my_strcmp(buffer, "env") == 0)
        print_array(shell->env);
    else if (find(buffer, "setenv ") == 0)
        my_setenv(&shell->env, cut_string(buffer, "setenv "));
    else if (find(buffer, "unsetenv ") == 0)
        my_unsetenv(&shell->env, cut_string(buffer, "unsetenv "));
    else if (find(buffer, "cd") == 0)
        shell->exit_value = my_cd(&shell->env, cut_string(buffer, "cd"));
    else
        shell->exit_value = exec_command(shell, buffer);
    return shell->env;
}

static void free_buffer_and_commands(char *buffer, char **commands) {
    free(buffer);
    free_array(commands);
}

void interpretor(t_shell *shell, char *buffer) {
    shell->commands = parse_input(buffer);
    for (int i = 0; shell->commands[i]; i++) {
        shell->env = command_launcher(shell, shell->commands[i]);
        if (shell->should_exit == 1) {
            return free_buffer_and_commands(buffer, shell->commands);
        }
    }
    free_buffer_and_commands(buffer, shell->commands);
}