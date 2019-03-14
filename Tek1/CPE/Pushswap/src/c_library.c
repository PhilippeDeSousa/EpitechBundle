#include "my.h"

int my_strlen(const char* s)
{
    int i = 0;

    for (i; s[i]; i++) {
    }
    return i;
}

void my_putstr(const int fd, const char* s, const char c)
{
    if (s)
        write(1, s, my_strlen(s));
    if (c)
        write(fd, &c, 1);
}

static int handle_negative(const char* s1, const char* s2)
{
    int tmp;
    int len1;
    int len2;

    if (s1[0] == '-' && s1[0] != s2[0])
        return -1;
    else if (s2[0] == '-' && s1[0] != s2[0])
        return 1;
    len1 = my_strlen(s1);
    len2 = my_strlen(s2);
    if (len1 != len2)
        return MAX(len1, len2);
    for (int i = 0; i < len1; i++)
        if (s1[i] - s2[i] != 0)
            return s1[i] - s2[i];
    return 0;
}

int my_strcmp(const char* s1, const char* s2)
{
    int len1;
    int len2;
    if (s1[0] == '-' || s2[0] == '-')
        return handle_negative(s1, s2);
    len1 = my_strlen(s1);
    len2 = my_strlen(s2);
    if (len1 != len2)
        return MAX(len1, len2);
    for (int i = 0; i < my_strlen(s1); i++)
        if (s1[i] - s2[i] != 0)
            return s1[i] - s2[i];
    return 0;
}