/*
** EPITECH PROJECT, 2018
** MAP
** File description:
** Header
*/

#ifndef MAP_H
# define MAP_H

# include "inventory.h"

/// Enum for the material type.
typedef enum {
	E_LINEMATE = 0,
	E_DERAUMERE = 1,
	E_SIBUR = 2,
	E_MENDIANE = 3,
	E_PHIRAS = 4,
	E_THYSTAME = 5,
	E_COUNT = 6,
} 	mats_e;

/// Material to string conversion
extern char *mats_names[E_COUNT];

/// Structure that is placed on every tile and contains all informations,
/// such as what is on the ground.
typedef struct 		map_s
{
	int 		x;
	int 		y;
	char		val;
	inventory_t	inv;
}			map_t;

#endif /* MAP_H */
