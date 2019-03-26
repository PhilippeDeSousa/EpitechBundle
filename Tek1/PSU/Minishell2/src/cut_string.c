#include "minishell.h"

char *cut_string(char *s1, const char *s2) {
    if (s1[my_strlen(s2)] == ' ')
        return &s1[my_strlen(s2) + 1];
    return &s1[my_strlen(s2)];
}