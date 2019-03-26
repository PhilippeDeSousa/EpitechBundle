#include "minishell.h"

int main(const int ac, char * const av[], const char * const *env) {
    (void)ac;
    (void)av;
    if (!env) {
        printf("No env, not handled yet\n");
    } else {
        return shell(env);
    }
}