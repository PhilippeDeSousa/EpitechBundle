#include "minishell.h"

static char **copy_env(const char * const *env) {
    char **new_env;
    size_t nb_lines;
    
    for (nb_lines = 0; env[nb_lines]; nb_lines++);
    new_env = malloc(sizeof(char *) * (nb_lines + 1));
    for (size_t i = 0; i < nb_lines; i++)
        new_env[i] = my_strdup(env[i]);
    new_env[nb_lines] = NULL;
    return (new_env);
}

static int display_prompt(char **env) {
    char *home = return_home(env);
    char *cwd = getcwd(NULL, 0);

    my_putstr(1, "~");
    my_putstr(1, cut_string(cwd, home));
    my_putstr(1, "> ");
    free(cwd);
    return (1);
}

static int interpretor(char ***env, char *buffer) {
    size_t exit_value = 0;

    if (my_strcmp(buffer, "env") == 0)
        print_array(*env);
    else if (find(buffer, "setenv ") == 0)
        my_setenv(env, cut_string(buffer, "setenv "));
    else if (find(buffer, "unsetenv ") == 0)
        my_unsetenv(env, cut_string(buffer, "unsetenv "));
    else if (find(buffer, "cd") == 0)
        exit_value = my_cd(env, cut_string(buffer, "cd"));
    else
        exit_value = exec_command(*env, buffer);
    return exit_value;
}

int should_exit(char **env, char *buffer, int *exit_value) {
    if (find(buffer, "exit") == 0) {
        if (!is_nbr(cut_string(buffer, "exit"))) {
            my_putstr(2, EXIT_ERR);
            *exit_value = 1;
            free(buffer);
            return 1;
        } else {
            *exit_value = my_exit(env, buffer, cut_string(buffer, "exit"), *exit_value);
            return (0);
        }
    }
    return 1;
}

int shell(const char * const *e) {
    char **env = copy_env(e);
    char *buffer;
    int exit_value = 0;

    while (display_prompt(env) && (buffer = get_next_line(0))) {
        if (buffer[0] == '\0') {
            free(buffer);
            continue;
        }
        buffer = epur_str(buffer);
        if (should_exit(env, buffer, &exit_value) == 0)
            return (exit_value);
        exit_value = interpretor(&env, buffer);
        free(buffer);
    }
    return (my_exit(env, buffer, NULL, exit_value));
}