#include "minishell.h"

static int set_values(char *str, char **var, char **val) {
    size_t pos;

    for (pos = 0; str[pos]; pos++)
        if (str[pos] == ' ') {
            str[pos] = '=';
            break;
        }
    if (pos == my_strlen(str)) {
        *var = add_equal(str);
        return (-1);
    }
    *var = malloc(sizeof(char) * (my_strlen(str)));
    my_strncpy(*var, str, pos + 1, 0);
    *val = malloc(sizeof(char) * (my_strlen(str) - 1));
    my_strncpy(*val, str, (my_strlen(str) - pos - 1), pos + 1);
    return (0);
}

static char **copy_env(char **env, size_t new_rows) {
    char **new_env;
    size_t nb_lines;
    
    for (nb_lines = 0; env[nb_lines]; nb_lines++);
    new_env = malloc(sizeof(char *) * (nb_lines + new_rows + 1));
    for (size_t i = 0; i < nb_lines; i++)
        new_env[i] = my_strdup(env[i]);
    new_env[nb_lines] = NULL;
    new_env[nb_lines + new_rows] = NULL;
    return (new_env);
}


static char **add_to_env(char **env, const char *var, const char *val) {
    char **new_env;
    
    int i = 0;
    new_env = copy_env(env, 1);
    for (i = 0; new_env[i]; i++);
    new_env[i] = my_strcat(var, val);
    free_array(env);
    return (new_env);
}

static char **apply_setenv(char **env, char *var, char *val) {
    for (size_t i = 0; env[i]; i++) {
        if (find(env[i], var) == 0) {
            free(env[i]);
            env[i] = my_strcat(var, val);
            return (env);
        }
    }
    env = add_to_env(env, var, val);
    return env;
}

int my_setenv(char ***env, char *str) {
    int nb_args = 0;
    char *var = NULL;
    char *val = NULL;

    for (int i = 0; str[i]; i++)
        if (str[i] == ' ')
            nb_args++;
    if (nb_args > 1) {
        my_putstr(2, SETENV_ERR);
        return (1);
    }
    else if (!str[0]) {
        print_array(*env);
    } else {
        set_values(str, &var, &val);
        *env = apply_setenv(*env, var, val);
        free(var);
        free(val);
    }
    return (0);
}