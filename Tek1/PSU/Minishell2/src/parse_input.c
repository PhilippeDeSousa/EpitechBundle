#include "minishell.h"

static t_tree set_empty_tree(char **tab)
{
    t_tree new;

    new.command = tab[0];
    new.left = NULL;
    new.right = NULL;
    return new;
}

static char **split_commands_semicolon(const char *buffer, int *i) {
    char **coms;
    int c;

    coms = str_to_array(buffer, ';');
    for (c = 0; coms[c]; c++) {
        if (!coms[c][0]) {
            free(coms[c]);
            coms[c] = NULL;
            break;
        }
    }
    *i = c;
    return coms;
}

void free_commands(char ***commands) {
    for (int i = 0; commands[i]; i++) {
        for (int c = 0; commands[i][c]; c++) {
            printf("Freeing: %s\n", commands[i][c]);
            free(commands[i][c]);
        }
        free(commands[i]);
    }
    free(commands);
}

void parse_input(t_shell *shell, const char *buffer) {
    int i;
    char **coms = split_commands_semicolon(buffer, &i);
    t_tree *tree;

    shell->free_commands = malloc(sizeof(char**) * (i + 1));
    for (i = 0; coms[i]; i++)
        shell->free_commands[i] = set_commands(coms[i]);
    shell->free_commands[i] = NULL;
    free_array(coms);
    tree = malloc(sizeof(t_tree) * (i + 1));
    for (i = 0; shell->free_commands[i]; i++) {
        if (arr_len(shell->free_commands[i]) == 1)
            tree[i] = set_empty_tree(shell->free_commands[i]);
        else
            create_tree(shell->free_commands[i], &tree[i]);
    }
    tree[i].command = NULL;
    shell->commands = tree;
}