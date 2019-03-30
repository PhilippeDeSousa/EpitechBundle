#include "minishell.h"

char **command_launcher(t_shell *shell, char *buffer) {
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
/*
static void free_tree(t_tree *tree) {
    if (tree->left) {
        free_tree(tree->left);
        //free(tree->left);
    }
    if (tree->right) {
        free_tree(tree->right);
        //free(tree->right);
    }
    printf("Commande free: %s\n", tree->command);
    free(tree);
}*/

void parse_tree(t_shell *shell, t_tree *tree) {
    char *command1;
    char *flag;
    char *command2;

    command1 = tree->left->command;
    command2 = tree->right->command;
    flag = tree->command;
    if (my_strcmp(flag, ">") == 0)
        handle_sup(shell, command1, command2, tree->left);
    if (my_strcmp(flag, "|") == 0)
        handle_pipe(shell, command1, command2);
}

void interpretor(t_shell *shell, char *buffer) {
    parse_input(shell, buffer);
    for (int i = 0; shell->commands[i].command; i++) {
        if (shell->commands[i].left == NULL) {
            shell->env = command_launcher(shell, shell->commands[i].command);
        }
        else {
            parse_tree(shell, &shell->commands[i]);
            //printf("Flags aren't handled yet\n");
            //print_tree(&shell->commands[i]);
        }
    }
    //free_tree(shell->commands);
    //free(shell->commands);
    //free_commands(shell->free_commands);
    free(buffer);
}