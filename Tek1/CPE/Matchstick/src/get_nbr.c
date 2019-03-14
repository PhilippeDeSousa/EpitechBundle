#include "matchstick.h"

static int is_nbr(const char *str)
{
    int i = 0;

    if (str[0] == '-')
        i++;
    for (i = i; str[i]; i++) {
        if (str[i] < '0' || str[i] > '9')
            return (-1);
    }
    return (0);
}

int	get_nbr(const char *str)
{
    int	i = 0;
    int	result = 0;
    int	sign = 1;

    if (str == NULL)
        return (0);
    if (is_nbr(str) < 0)
        return (-1); // Not printing an error
    if (str[0] == '-') {
        sign = -1;
        i++;
    }
    for (i = i; str[i]; i++)
        result = result * 10 + str[i] - '0';
    return (sign * result);
}
