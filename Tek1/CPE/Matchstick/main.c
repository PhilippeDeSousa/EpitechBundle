#include "matchstick.h"

int main(const int ac, const char * const *av)
{
    int size = get_nbr(av[1]);
    int nb = get_nbr(av[2]);

    if (ac != 3 || size <= 0 || size >= 100 || nb <= 0) {
        my_putstr(1, "Wrong parameters\n");
        return (84);
    }
    return matchstick(size, nb);
}