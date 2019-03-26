#include "minishell.h"

static size_t nb_sep(const char *str, char sep) {
    size_t nb = 0;

    for (size_t i = 0; str[i]; i++) {
        if (str[i] == sep)
            nb++;
    }
    return (nb + 1);
}

static char *write_line(const char *str, char sep) {
    static size_t pos = 0;
    size_t next_sep;
    size_t i = 0;
    size_t tmp;
    size_t c = 0;
    char *line;

    for (size_t nb_sep = 0; str[i] && nb_sep < pos; i++)
        if (str[i] == sep)
            nb_sep++;
    tmp = i;
    for (next_sep = 0; str[i] && str[i] != sep; i++, next_sep++);
    line = malloc(sizeof(char) * (next_sep + 2));
    i = tmp;
    for (c = 0; i < (tmp + next_sep); i++, c++)
        line[c] = str[i];
    line[c] = '/';
    line[c + 1] = '\0';
    pos++;
    return (line);
}

char **parse_env(const char *str, char sep) {
    size_t seps = nb_sep(str, sep);
    char **arr = malloc(sizeof(char *) * (seps + 1));
    size_t i = 0;

    for ( ; i < seps; i++)
        arr[i] = write_line(str, sep);
    arr[i] = NULL;
    return (arr);
}

char **get_all_paths(char **env) {
    for (int i = 0; env[i]; i++) {
        if (find(env[i], "PATH=") == 0) {
            return (parse_env(cut_string(env[i], "PATH="), ':'));
        }
    }
    return (NULL);
}