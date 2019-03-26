#include "minishell.h"

int is_nbr(const char *str) {
    for (int i = 0; str[i]; i++) {
        if (str[i] < '0' || str[i] > '9')
            return (0);
    }
    return (1);
}

int my_exit(char **env, char *buffer, const char *val, size_t exit_value) {
    int return_val = 0;

    free_array(env);
    if (val == NULL || val[0] == '\0') {
        free(buffer);
        return (exit_value);
    }
    if (!is_nbr(val)) {
        my_putstr(2, EXIT_ERR);
        return (-1);
    }
    return_val = convertnb(val);
    if (return_val > 255 || return_val < 0)
        return_val = 255;
    free(buffer);
    return (return_val);
}