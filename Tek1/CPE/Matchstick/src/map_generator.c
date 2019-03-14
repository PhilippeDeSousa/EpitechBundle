#include <matchstick.h>

static char *set_line(char *line, int i, int size)
{
    int sp = size - i;
    int len = (i * 2) - 1 + sp;
    int x;

    line[0] = '*';
    for (x = 1; x <= sp; x++)
        line[x] = ' ';
    for (x = x; x <= len; x++)
        line[x] = '|';
    for (x = x; x <= sp + len; x++)
        line[x] = ' ';
    line[x] = '*';
    line[x + 1] = '\0';
    return (line);
}

static char *first_last_lines(const int size)
{
    char *line = malloc(sizeof(char) * (size * 2 + 2));
    int max = (size * 2) + 1;
    int i;

    if (line == NULL)
        return (NULL);
    for (i = 0; i < max; i++)
        line[i] = '*';
    line[i] = '\0';
    return (line);
}

char **create_map(const int size)
{
    char **map = malloc(sizeof(char *) * (size + 3));
    int y = 1;

    map[0] = first_last_lines(size);
    for (int i = 1; i <= size; i++) {
        map[y] = malloc(sizeof(char) * (size * 2 + 2));
        map[y] = set_line(map[y], i, size);
        y++;
    }
    map[y] = first_last_lines(size);
    map[y + 1] = NULL;
    return (map);
}