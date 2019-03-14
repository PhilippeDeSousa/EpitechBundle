#include "matchstick.h"

static int get_matches(char **map, int line)
{
    int	nb = 0;

    for (int c = 0; map[line][c]; c++)
        if (map[line][c] == '|')
	        nb++;
    return (nb);
}

static int single_stick(char **map, int line)
{
    for (int i = 0; map[i] && line == -1; i++)
        if ((get_matches(map, i)) > 0)
            line = i;
    return (line);
}

static int select_line(char **map, int *line)
{
    int xor = 0;

    for (int i = 0; map[i]; i++)
        xor ^= get_matches(map, i);
    for (int i = 0; map[i] && *line == -1; i++)
        if ((xor ^ get_matches(map, i)) < get_matches(map, i))
            *line = i;
    if (*line <= 0)
        *line = single_stick(map, *line);
    return xor;
}

static void	final_check(char **board, int *line, int *sticks)
{
    int	j = 0;
    int	k = 0;

    for (int i = 0; board[i]; i++) {
        if ((get_matches(board, i)) == 1)
	        k += 1;
        if ((get_matches(board, i)) != 0)
	        j += 1;
    }
    if ((k + 1) == j) {
        for (int i = 0; board[i]; i++) {
            if ((get_matches(board, i)) > 1)
                *line = i;
            *sticks = (k % 2 != 0) ? get_matches(board, *line) : get_matches(board, *line) - 1;
	    }
    }
}

char **ai_turn(char **map, const int nb)
{
    int xor = 0;
    int line = -1;
    int matches = -1;

    xor = select_line(map, &line);
    matches = ((get_matches(map, line)) -
            (xor ^ (get_matches(map, line))));
    final_check(map, &line, &matches);
    matches = (matches > nb) ? nb : (matches == 0) ? 1 : matches;
    map = remove_matches(map, line, matches, AI);
    display_map(map);
    return map;
}