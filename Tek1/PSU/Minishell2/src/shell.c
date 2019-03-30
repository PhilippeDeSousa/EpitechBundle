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

static void init_shell(t_shell *shell, const char * const *e) {
    shell->exit_value = 0;
    shell->should_exit = 0;
    shell->env = copy_env(e);
    shell->paths = get_all_paths(shell->env);
}

int shell(const char * const *e) {
    t_shell shell;
    char *buffer;

    init_shell(&shell, e);
    (isatty(0)) ? display_prompt(shell.env) : 0;
    while ((buffer = get_next_line(0))) {
        if (buffer[0] == '\0') {
            free(buffer);
            continue;
        }
        interpretor(&shell, epur_str(buffer));
        if (shell.should_exit == 1)
            return (shell.exit_value);
        (isatty(0)) ? display_prompt(shell.env) : 0;
    }
    return (my_exit(&shell, NULL));
}