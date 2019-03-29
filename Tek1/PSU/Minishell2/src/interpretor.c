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
}

/*static void flag_handler(t_shell *shell, t_tree *tree) {
    (void)shell;
    (void)tree;
}*/

void interpretor(t_shell *shell, char *buffer) {
    parse_input(shell, buffer);
    for (int i = 0; shell->commands[i].command; i++) {
        printf("Priting tree:\n");
        if (shell->commands[i].left == NULL) {
            shell->env = command_launcher(shell, shell->commands[i].command);
        }
        else {
            printf("Flags aren't handled yet\n");
            print_tree(&shell->commands[i]);
        }
    }
    //free(shell->commands);
    free_commands(shell->free_commands);
    free(buffer);
}