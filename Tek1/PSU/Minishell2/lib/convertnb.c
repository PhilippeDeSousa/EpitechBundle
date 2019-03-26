#include "minishell.h"

int convertnb(const char *str)
{
    int i = 0;
    int result = 0;
    int sign = 1;

    if (!str)
        return (0);
    if (str[0] == '-') {
        sign = -1;
        i++;
    }
    for ( ; str[i] != '\0'; i++) {
        result = result * 10 + str[i] - '0';
    }
    return (sign * result);
}