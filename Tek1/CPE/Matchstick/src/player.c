#include "matchstick.h"

#include <stdio.h>

static int get_position(char **map)
{
    char *entry;
    int pos;
    int y;

    my_putstr(1, "Line: ");
    entry = get_next_line(0);
    if (entry == NULL)
        exit(0);
    for (y = 1; map[y]; y++);
    if ((pos = get_nbr(entry)) < 1 || pos > y - 2) {
        my_putstr(1, "Error: this line is out of range\n");
        return (get_position(map));
    }
    free(entry);
    return pos;
}

static int get_matches(char **map, int line, int max)
{
    char *entry;
    int nb;

    my_putstr(1, "Matches: ");
    entry = get_next_line(0);
    if (entry == NULL)
        exit(0);
    if ((nb = get_nbr(entry)) < 1 || nb > max) {
        printf("Error: you cannot remove more than %d matches per turn\n", max);
        return (-1);
    }
    if (nb > nb_matches(map, line)) {
        my_putstr(1, "Error: not enough matches on the line\n");
        return -1;
    }
    free(entry);
    return nb;
}

char **player_turn(char **map, const int nb)
{
    int line;
    int matches;

    while (1) {
        line = get_position(map);
        matches = get_matches(map, line, nb);
        if (matches != -1) {
            map = remove_matches(map, line, matches, PLAYER);
            break;
        }
    }
    display_map(map);
    return map;
}