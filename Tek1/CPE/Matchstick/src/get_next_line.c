/* This file contains the get_next_line function */

#include "get_next_line.h"
#include <stdio.h>

static size_t my_strlen(char* str)
{
    size_t i;

    for (i = 0; str[i]; i++) {
    }
    return i;
}

static char* my_realloc(char* str)
{
    char* ret;
    size_t i;
    size_t size = my_strlen(str) + 2;

    if ((ret = malloc(sizeof(char) * size)) == NULL)
        return (NULL);
    for (i = 0; str[i] != '\0'; i++)
        ret[i] = str[i];
    ret[i + 1] = '\0';
    free(str);
    return ret;
}

static char get_buff(const int fd)
{
    static char buff[READ_SIZE];
    static char* ptr;
    static int rd_val = 0;
    char c;

    if (rd_val == 0) {
        rd_val = read(fd, buff, READ_SIZE);
        if (rd_val == 0 || my_strlen(buff) == 0)
            return '\0';
        ptr = buff;
    }
    c = *ptr;
    ptr += 1;
    rd_val -= 1;
    return c;
}

static char* return_line(char* line, int i, char buff)
{
    line[i] = '\0';
    if (!buff) {
        if (line && my_strlen(line) > 1)
            return line;
        free(line);
        return NULL;
    }
    return line;
}

char* get_next_line(const int fd)
{
    int i = 0;
    char buff;
    char* line = malloc(sizeof(char) * 2);

    if (line == NULL)
        return NULL;
    line[1] = '\0';
    buff = get_buff(fd);
    for (i = 0; buff && buff != '\n'; i++) {
        line[i] = buff;
        line = my_realloc(line);
        buff = get_buff(fd);
    }
    return return_line(line, i, buff);
}
