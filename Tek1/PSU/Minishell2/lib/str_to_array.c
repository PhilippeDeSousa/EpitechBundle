#include <stdlib.h>
#include <stdio.h>

static size_t nb_sep(const char *str, char sep) {
    size_t nb = 0;

    for (size_t i = 0; str[i]; i++) {
        if (str[i] == sep)
            nb++;
    }
    return (nb + 1);
}

static char *write_line(const char *str, char sep, size_t pos) {
    size_t next_sep;
    size_t i = 0;
    size_t tmp;
    size_t c = 0;
    char *line;

    for (size_t nb_sep = 0; str[i] && (nb_sep < pos); i++)
        if (str[i] == sep)
            nb_sep++;
    tmp = i;
    for (next_sep = 0; str[i] && str[i] != sep; i++, next_sep++);
    line = malloc(sizeof(char) * (next_sep + 1));
    i = tmp;
    for (c = 0; i < (tmp + next_sep); i++, c++)
        line[c] = str[i];
    line[c] = '\0';
    return (line);
}

char **str_to_array(const char *str, char sep) {
    size_t seps = nb_sep(str, sep);
    char **arr = malloc(sizeof(char *) * (seps + 1));
    size_t i = 0;

    for ( ; i < seps; i++) {
        arr[i] = write_line(str, sep, i);
    }
    arr[i] = NULL;
    return (arr);
}