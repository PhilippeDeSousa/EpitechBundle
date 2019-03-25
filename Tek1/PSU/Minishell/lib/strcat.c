#include "minishell.h"

char *my_strcat(const char *s1, const char *s2) {
    char *str = malloc(sizeof(char) * (my_strlen(s1) + my_strlen(s2) + 1));
    int i = 0;
    int ii;

    if (s1) {
        for (ii = 0; s1[ii]; ii++, i++)
            str[i] = s1[ii];
    }
    if (s2) {
        for (ii = 0; s2[ii]; ii++, i++)
            str[i] = s2[ii];
    }
    str[i] = '\0';
    return (str);
}

char *form_directory(const char *s1, const char *s2) {
    char *str = malloc(sizeof(char) * (my_strlen(s1) + my_strlen(s2) + 2));
    int i = 0;
    int ii;

    if (s1) {
        for (ii = 0; s1[ii]; ii++, i++)
            str[i] = s1[ii];
    }
    str[i] = '/';
    i++;
    if (s2) {
        for (ii = 0; s2[ii]; ii++, i++)
            str[i] = s2[ii];
    }
    str[i] = '\0';
    return (str);
}