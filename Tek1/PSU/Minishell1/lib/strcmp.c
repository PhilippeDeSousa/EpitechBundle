#include "minishell.h"

int my_strcmp(const char *s1, const char *s2) {
    if (my_strlen(s1) != my_strlen(s2))
        return (my_strlen(s2) - my_strlen(s1));
    for (int i = 0; s1[i] && s2[i]; i++) {
        if (s1[i] != s2[i])
            return (s2[i] - s1[i]);
    }
    return (0);
}

int find(const char *src, const char *f) {
    for (int i = 0; src[i] && f[i]; i++) {
        if (src[i] != f[i])
            return (f[i] - src[i]);
    }
    return (0);
}