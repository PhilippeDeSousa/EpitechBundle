#include "matchstick.h"

#include <stdio.h>

char **remove_matches(char **map, int line, int matches, int player)
{
    int save = matches;

    for (int x = my_strlen(map[line]); x > 0 && matches > 0; x--) {
        if (map[line][x] == '|') {
            map[line][x] = ' ';
            matches -= 1;
        }
    }
    if (player == PLAYER)
        printf("Player removed %d match(es) from line %d\n", save, line);
    if (player == AI)
        printf("AI removed %d match(es) from line %d\n", save, line);
    return map;
}

int nb_matches(char **map, int line)
{
    int nb = 0;

    for (int x = 0; map[line][x]; x++)
        if (map[line][x] == '|')
            nb++;
    return nb;
}

int game_over(char **map, int player)
{
    int nb_matches = 0;

    for (int y = 0; map[y]; y++)
        for (int x = 0; map[y][x]; x++)
            if (map[y][x] == '|')
                nb_matches++;
    if (nb_matches <= 1) {
        if (player == PLAYER)
            my_putstr(1, "You lost, too bad...\n");
        if (player == AI)
            my_putstr(1, "I lost... snif... but I'll get you next time!!\n");
        for (int y = 0; map[y]; y++)
            free(map[y]);
        free(map);
        return player;
    }
    return -1;
}