/*
** EPITECH PROJECT, 2018
** Sokoban
** File description:
** Sokoban
*/

#include <my.h>
#include <stdlib.h>

void set_player(t_map **map, t_player *player)
{
    for (int y = 0; map[y]; y++)
        for (int x = 0; map[y][x].old; x++)
            if (map[y][x].old == PLAYER) {
                map[y][x].old = ' ';
                player->x = x;
                player->y = y;
            }
}

void move_player(t_map **map, t_player *player, int x, int y)
{
    if (map[player->y + y][player->x + x].cur && map[player->y + y][player->x + x].cur != WALL) {
        if (map[player->y + y][player->x + x].cur != BOX) {
            map[player->y + y][player->x + x].cur = PLAYER;
            map[player->y][player->x].cur = map[player->y][player->x].old;
            player->x = player->x + x;
            player->y = player->y + y;
        }
        else if (map[player->y + y * 2][player->x + x * 2].cur && map[player->y + y * 2][player->x + x * 2].cur != WALL) {
            map[player->y + y][player->x + x].cur = PLAYER;
            if (map[player->y][player->x].old == HOLE)
                map[player->y][player->x].cur = map[player->y][player->x].old;
            else {
                map[player->y][player->x].old = SPACE;
                map[player->y][player->x].cur = SPACE;
            }
            map[player->y + y * 2][player->x + x * 2].cur = BOX;
            player->x = player->x + x;
            player->y = player->y + y;
        }
    }
}

static int check_win(t_map **map)
{
    for (int y = 0; map[y]; y++) {
        for (int x = 0; map[y][x].cur; x++)
            if (map[y][x].cur == HOLE)
                return 0;
    }
    return 1;
}

static void game_loop(t_map **map, t_player player)
{
    keypad(stdscr, TRUE);
    for (int ent = getch(); ent != 27; ent = getch()) {
        switch(ent) {
            case KEY_RIGHT:
                move_player(map, &player, 1, 0);
                break;
            case KEY_LEFT:
                move_player(map, &player, -1, 0);
                break;
            case KEY_UP:
                move_player(map, &player, 0, -1);
                break;
            case KEY_DOWN:
                move_player(map, &player, 0, 1);
                break;
        }
        print_map(map);
        if (check_win(map))
            break;
    }
    endwin();
}

int sokoban(t_map **map)
{
    t_player player;

    initscr();
    noecho();
    curs_set(FALSE);
    set_player(map, &player);
    print_map(map);
    game_loop(map, player);
    free_map(map);
    return 0;
}