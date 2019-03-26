#include "minishell.h"

char *my_strdup(const char *str) {
    char *new = malloc(sizeof(char) * my_strlen(str) + 1);
    int i;

    for (i = 0; str[i]; i++) {
        new[i] = str[i];
    }
    new[i] = '\0';
    return (new);
}

char *add_equal(const char *str) {
    char *new = malloc(sizeof(char) * my_strlen(str) + 2);
    int i;

    for (i = 0; str[i]; i++) {
        new[i] = str[i];
    }
    new[i] = '=';
    new[i + 1] = '\0';
    return (new);
}