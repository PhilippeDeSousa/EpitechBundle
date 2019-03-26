#include "minishell.h"

static int does_exist(char **env, const char *var) {
    for (size_t i = 0; env[i]; i++) {
        if (find(env[i], var) == 0)
            return i;
    }
    return -1;
}

char **remove_from_env(char **env, int pos) {
    char **new_env;
    int nb_lines;
    int i = 0;
    int c;
    
    for (nb_lines = 0; env[nb_lines]; nb_lines++);
    new_env = malloc(sizeof(char *) * (nb_lines + 1));
    for (i = 0; i < pos; i++)
        new_env[i] = my_strdup(env[i]);
    for (c = pos + 1; c < nb_lines; i++, c++) {
        new_env[i] = my_strdup(env[c]);
    }
    new_env[i] = NULL;
    free_array(env);
    return (new_env);
}

int my_unsetenv(char ***env, char *var) {
    int pos;

    if ((pos = does_exist(*env, var)) == -1)
        return (-1);
    *env = remove_from_env(*env, pos);
    return (0);
}