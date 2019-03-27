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

static void free_buffer_and_commands(char *buffer, t_command **commands) {
    free(buffer);
    for (int i = 0; commands[i]; i++) {
        for (int c = 0; commands[i][c].content; c++)
            free(commands[i][c].content);
        free(commands[i]);
    }
    free(commands);
}

void interpretor(t_shell *shell, char *buffer) {
    shell->command = parse_input(buffer);
    for (int i = 0; shell->command[i]; i++) {
        for (int c = 0; shell->command[i][c].content; c++) {
            if (shell->command[i][c].type == COMMAND) {
                shell->env = command_launcher(shell, shell->command[i][c].content);
                if (shell->should_exit == 1) {
                    free_buffer_and_commands(buffer, shell->command);
                    return;
                }
            }
            if (shell->command[i][c].type == FLAG)
                printf("Flags are not handled yet, but I found a %s\n", shell->command[i][c].content);
        }
    }
    free_buffer_and_commands(buffer, shell->command);
}