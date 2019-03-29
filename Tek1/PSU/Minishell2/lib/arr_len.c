#include <unistd.h>

size_t arr_len(char **arr) {
    int i = 0;
    
    for ( ; arr[i]; i++);
    return (i);
}