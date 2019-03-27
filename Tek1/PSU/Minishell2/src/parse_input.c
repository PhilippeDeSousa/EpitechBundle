#include "minishell.h"

static size_t nb_flags(const char *str) {
    size_t nb = 0;

    for (size_t i = 0; str[i]; i++) {
        if (str[i] == '>' || str[i] == '<' || str[i] == '|' || str[i] == '&') {
            nb++;
            if (str[i + 1] && (str[i + 1] == str[i])) {
                nb--;
            }
        }
    }
    return (nb + 1);
}

static int is_flag(char c, char d) {
    if (c == '>' || c == '<' || c == '|' || c == '&') {
        if (c == d)
            return 2;
        return 1;
    }
    return 0;
}

static char *set_line(const char *buffer, int *i) {
    char *line;
    int other_tmp = *i;
    int tmp = *i;
    int c;

    for ( ; buffer[other_tmp] && !(is_flag(buffer[other_tmp], buffer[other_tmp + 1])); other_tmp++);
    line = malloc(sizeof(char) * (other_tmp - tmp + 1));
    for (c = 0; tmp < other_tmp; tmp++, c++) {
        line[c] = buffer[tmp];
    }
    line[c] = '\0';
    *i = other_tmp;
    return epur_str(line);
}

static char *set_flag(const char *buffer, int *i, int flag_size) {
    char *line = malloc(sizeof(char) * (flag_size + 1));
    int tmp = *i;

    line[0] = buffer[tmp];
    if (flag_size == 2) {
        line[1] = buffer[tmp];
    }
    line[flag_size] = '\0';
    *i = tmp + 1;
    return (line);
}

static t_command *set_commands(const char *buffer) {
    t_command *com = malloc(sizeof(t_command) * (nb_flags(buffer) * 2 + 1));
    int buffer_size = my_strlen(buffer);
    int c = 0;
    int size = 0;

    for (int i = 0; buffer[i]; i++) {
        com[c].type = COMMAND;
        com[c].content = set_line(buffer, &i);
        if (i >= buffer_size)
            break;
        c++;
        if (buffer[i] && buffer[i + 1] && (size = is_flag(buffer[i], buffer[i +1]))) {
            com[c].type = FLAG;
            com[c].content = epur_str(set_flag(buffer, &i, size));
            c++;
        }
    }
    com[c + 1].content = NULL;
    return com;
}

t_command **parse_input(const char *buffer) {
    t_command **commands;
    char **coms;
    int i;

    coms = str_to_array(buffer, ';');
    for (i = 0; coms[i]; i++) {
        if (!coms[i][0]) {
            free(coms[i]);
            coms[i] = NULL;
            break;
        }
    }
    commands = malloc(sizeof(t_command*) * (i + 1));
    for (i = 0; coms[i]; i++)
        commands[i] = set_commands(coms[i]);
    commands[i] = NULL;
    free_array(coms);
    return commands;
}