#include "matchstick.h"

static int game(char **map, const int nb)
{
    int ret = -1;

    while (1) {
        if ((ret = game_over(map, PLAYER)) != -1)
            return ret;
        my_putstr(1, "\nYour turn:\n");
        map = player_turn(map, nb);
        if ((ret = game_over(map, AI)) != -1)
            return ret;
        my_putstr(1, "\nAI's turn...\n");
        map = ai_turn(map, nb);
    }
    return (0);
}

int matchstick(const int size, const int nb)
{
    char **map = create_map(size);

    if (map == NULL)
        return (84);
    display_map(map);
    return game(map, nb);
}