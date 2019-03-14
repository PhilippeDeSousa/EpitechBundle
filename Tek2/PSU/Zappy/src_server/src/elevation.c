/*
** EPITECH PROJECT, 2018
** Project description
** File description:
** Description here
*/

#include "server.h"
#include "map.h"
#include <stdbool.h>

/// Requirements for every elevation level
static const inventory_t g_req[8] = {
		{1, 1, 0, 0, 0, 0, 0, 0},
		{2, 2, 1, 1, 0, 0, 0, 0},
		{2, 2, 0, 1, 0, 2, 0, 0},
		{4, 1, 1, 2, 0, 1, 0, 0},
		{4, 1, 2, 1, 3, 0, 0, 0},
		{6, 1, 2, 3, 0, 1, 0, 0},
		{6, 2, 2, 2, 2, 2, 1, 0}
};

/// Elevates everyone on the tile
/// @param serv
/// @param cl
/// @return
static int elevate_everyone(server_t *serv, client_t *cl)
{
	int i = 0;

	for (i = 0; i < serv->nb_clients - 1; i++) {
		if (serv->clients[i] && serv->clients[i]->x == cl->x &&
			serv->clients[i]->y == cl->y
			&& serv->clients[i]->level == cl->level) {
				serv->clients[i]->level += 1;
				dprintf(serv->clients[i]->sock,
				"Elevation underway, current level %d\n",
				serv->clients[i]->level - 1);
			}
	}
	serv->map[cl->y][cl->x].inv.l -= g_req[i].l;
	serv->map[cl->y][cl->x].inv.d -= g_req[i].d;
	serv->map[cl->y][cl->x].inv.s -= g_req[i].s;
	serv->map[cl->y][cl->x].inv.m -= g_req[i].m;
	serv->map[cl->y][cl->x].inv.p -= g_req[i].p;
	serv->map[cl->y][cl->x].inv.t -= g_req[i].t;
	return (0);
}

/// Verifies if there are enough resources, then it will elevate every clients
/// @param cl
/// @param serv
/// @param common
/// @return -1 if failed
static int check_requirements(client_t *cl, server_t *serv, inventory_t *common)
{
	int i = cl->level - 2;

	if (common->players < g_req[i].players ||
		common->l < g_req[i].l || common->d < g_req[i].d ||
		common->s < g_req[i].s || common->m < g_req[i].m ||
		common->p < g_req[i].p || common->t < g_req[i].t)
			return (elevate_everyone(serv, cl));
	else
		return (-1);
}

/// Pools the resources of every players and test if the requirements are met
/// @param cl
/// @param serv
/// @return
static int combine_ressources(client_t *cl, server_t *serv)
{
	inventory_t combined;

	combined.players = 0;
	combined.l = serv->map[cl->y][cl->x].inv.l;
	combined.d = serv->map[cl->y][cl->x].inv.d;
	combined.s = serv->map[cl->y][cl->x].inv.s;
	combined.m = serv->map[cl->y][cl->x].inv.m;
	combined.p = serv->map[cl->y][cl->x].inv.p;
	combined.t = serv->map[cl->y][cl->x].inv.t;
	for (int i = 0; i < serv->nb_clients - 1; i++) {
		if (serv->clients[i] && serv->clients[i]->x == cl->x &&
			serv->clients[i]->y == cl->y
			&& serv->clients[i]->level == cl->level)
			combined.players += 1;
	}
	return (check_requirements(cl, serv, &combined));
}

/// Elevates the client,
/// to win, 6 players from a team need to reach maximum elevation.
/// @param cl
/// @param serv
/// @param input
void elevation(client_t *cl, server_t *serv, char *input)
{
	int target_lvl = cl->level + 1;

	if (target_lvl >= 8 || strcmp(input, "Incantation"))
		return;
	else {
		if (combine_ressources(cl, serv) == -1)
			return;
		else {
			cl->cmd = 1;
			cl->action = get_time((double)300.00f / serv->freq);
			wait_timer(cl);
		}
	}
}
