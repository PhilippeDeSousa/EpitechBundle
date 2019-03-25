#include "minishell.h"
#include "sys/types.h"
#include "sys/stat.h"

char *return_home(char **env) {
    for (int i = 0; env[i]; i++) {
        if (find(env[i], "HOME=") == 0)
            return (cut_string(env[i], "HOME="));
    }
    return (NULL);
}

static int change_directory(char ***env, const char *dir, const char *current) {
    char *tmp;
    char *pwd;
    char *oldpwd;

    if (chdir(dir) == -1) {
        return (-1);
    }
    tmp = getcwd(NULL, 0);
    pwd = my_strcat("PWD ", tmp);
    my_setenv(env, pwd);
    oldpwd = my_strcat("OLDPWD ", current);
    my_setenv(env, oldpwd);
    free(tmp);
    free(pwd);
    free(oldpwd);
    return (0);
}

static int is_directory(const char *new_dir) {
    struct stat path_stat;
    if (stat(new_dir, &path_stat) != 0)
        return (0);
    return S_ISREG(path_stat.st_mode);
}

int my_cd(char ***env, const char *dir) {
    int ret_val = 0;
    char *home;
    char *current = getcwd(NULL, 0);
    char *new_dir;

    if (!dir[0]) {
        home = return_home(*env);
        if ((ret_val = change_directory(env, home, current)) == -1)
            my_puterr(2, "cd", HOMEDIR_ERR);
    } else {
        new_dir = form_directory(current, dir);
        if ((ret_val = change_directory(env, new_dir, current)) == -1) {
            if (is_directory(new_dir) != 0) {
                my_puterr(2, dir, NOT_DIR);
            } else
                my_puterr(2, dir, NO_SUCH_FILE);
        }
        free(new_dir);
    }
    free(current);
    return (ret_val);
}