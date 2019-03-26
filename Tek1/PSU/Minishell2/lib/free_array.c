#include "stdlib.h"

void free_array(char **env) {
    for (int i = 0; env[i]; i++)
        free(env[i]);
    free(env);
}