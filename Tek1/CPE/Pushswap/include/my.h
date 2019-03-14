#ifndef MY_LIST_H
#define MY_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX(x, y) (((x) > (y)) ? (1) : (-1))

typedef struct s_list {
    char* data;
    struct s_list* next;
} t_list;

t_list* add_to_list(t_list* list, char* nb);

void my_putstr(const int, const char*, const char);
int my_list_size(t_list* begin);

int my_strcmp(const char* s1, const char* s2);

t_list* del_first(t_list* list);
t_list* pa(t_list* list, t_list* pile);
t_list* pb(t_list* list, t_list* pile);
t_list* sa(t_list* list);

void sort_list(t_list* list, t_list* pile);

//DEBUGGING
void print_list(t_list* list);

#endif /*MY_LIST*/
