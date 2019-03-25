#include "minishell.h"

static char *remove_first(char *new) {
    size_t d = 0;

    if (new[0] == ' ') {
        for (d = 0; new[d] && new[d + 1]; d++) {
            new[d] = new[d + 1];
        }
        new[d] = '\0';
    }
    return (new);
}

char *epur_str(char *str) {
    char *new = malloc(sizeof(char) * my_strlen(str) + 1);
    size_t d = 0;

    for (size_t i = 0; str[i]; i++)
        if (str[i] == '\t')
            str[i] = ' ';
    for (size_t c = 0; str[c] != '\0'; c++, d++) {
        if (str[c] == ' ') {
            for (size_t tmp = c + 1; str[tmp] == ' ' && str[tmp] != '\0'; tmp++)
                if (str[tmp] == ' ')
                    c++;
        }
        new[d] = str[c];
    }
    if (new[d - 1] == ' ')
        new[d - 1] = '\0';
    new[d] = '\0';
    free(str);
    return remove_first(new);
}