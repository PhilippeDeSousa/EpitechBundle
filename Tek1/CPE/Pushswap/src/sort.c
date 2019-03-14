#include "my.h"

int check_end(t_list* list)
{
    for (int a = my_list_size(list);
         list->next && my_strcmp(list->data, list->next->data) <= 0; a--)
        list = list->next;
    if (!list->next)
        return (0);
    return 1;
}

void sort_list(t_list* list, t_list* pile)
{
    int size = my_list_size(list);

    while (check_end(list) > 0) {
        for (int i = size; i >= 2; i--) {
            if (my_strcmp(list->data, list->next->data) > 0)
                list = sa((list));
            pile = pb(list, pile);
            list = del_first(list);
        }
        for (int c = my_list_size(pile); c > 0; c--) {
            list = pa(list, pile);
            pile = del_first(pile);
        }
    }
    free(list);
}