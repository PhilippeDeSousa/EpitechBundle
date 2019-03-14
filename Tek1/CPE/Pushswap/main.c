#include "my.h"

/* DEBUGGING ONLY */

void print_list(t_list* list)
{
    while (list != NULL) {
        my_putstr(1, list->data, ' ');
        list = list->next;
    }
    my_putstr(1, NULL, '\n');
}

static t_list* my_rev_list(t_list* list)
{
    t_list* next;
    t_list* tmp;

    tmp = NULL;
    while (list != NULL) {
        next = list->next;
        list->next = tmp;
        tmp = list;
        list = next;
    }
    return (tmp);
}

int my_list_size(t_list* begin)
{
    int i = 0;

    for (i; begin; i++)
        begin = begin->next;
    return (i);
}

int main(int ac, char** av)
{
    t_list* list = NULL;
    t_list* pile = NULL;

    for (int i = 1; i < ac; i++)
        list = add_to_list(list, av[i]);
    list = my_rev_list(list);
    sort_list(list, pile);
    my_putstr(1, NULL, '\n');
    return (0);
}
