#include "minishell.h"

char **parse_input(const char *buffer) {
    char **commands;

    commands = str_to_array(buffer, ';');
    for (int i = 0; commands[i]; i++) {
        if (!commands[i][0]) {
            free(commands[i]);
            commands[i] = NULL;
            break;
        }
        commands[i] = epur_str(commands[i]);
    }
    return commands;
}