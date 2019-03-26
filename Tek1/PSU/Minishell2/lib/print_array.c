#include "minishell.h"

void print_array(char **arr) {
    for (int i = 0; arr[i]; i++) {
        my_putstr(1, arr[i]);
        my_putstr(1, "\n");
    }
}