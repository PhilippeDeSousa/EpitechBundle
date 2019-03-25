#include "minishell.h"

char *my_strncpy(char *dest, const char *src, size_t n, size_t offset)
{
    size_t ii = 0;
    size_t i = offset;

    for ( ; i < (n + offset) && src[i] != '\0'; i++) {
        dest[ii] = src[i];
        ii++;
    }
    dest[ii] = '\0';
    return dest;
}
