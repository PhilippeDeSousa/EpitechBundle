#include <unistd.h>

int my_strlen(const char *str)
{
    int i;

    for (i = 0; str[i]; i++) {
    }
    return (i);
}

void my_putstr(const int fd, const char *str)
{
    write(fd, str, my_strlen(str));
}

void display_map(char **map)
{
    for (int y = 0; map[y]; y++) {
        my_putstr(1, map[y]);
        my_putstr(1, "\n");
    }
}