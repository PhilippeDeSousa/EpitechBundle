#include "minishell.h"

size_t my_strlen(const char *str) {
    size_t i;

    if (!str)
        return (0);
    for (i = 0; str[i]; i++);
    return (i);
}

void my_putstr(const int fd, const char *str) {
    write(fd, str, my_strlen(str));
}

void my_puterr(const int fd, const char *s1, const char *s2) {
    write(fd, s1, my_strlen(s1));
    write(fd, s2, my_strlen(s2));
}