#include "my.h"

t_list* pb(t_list* list, t_list* pile)
{
    pile = add_to_list(pile, list->data);
    my_putstr(1, "pb ", '\0');
    return (pile);
}

t_list* pa(t_list* list, t_list* pile)
{
    list = add_to_list(list, pile->data);
    my_putstr(1, "pa ", '\0');
    return (list);
}

t_list* sa(t_list* list)
{
    char* tmp = list->next->data;

    if (my_list_size(list) >= 2) {
        list->next = list->next->next;
        list = add_to_list(list, tmp);
        my_putstr(1, "sa ", '\0');
    }
    return (list);
}

t_list* add_to_list(t_list* list, char* str)
{
    t_list* tmp = malloc(sizeof(t_list));

    if (tmp) {
        tmp->data = str;
        tmp->next = list;
    }
    return (tmp);
}

t_list* del_first(t_list* list)
{
    t_list* tmp = list->next;
    free(list);
    return (tmp);
}