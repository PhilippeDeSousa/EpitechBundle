/*
** EPITECH PROJECT, 2018
** Project description
** File description:
** Description here
*/

#include "AI.hpp"

int zappy::AI::isMaterialNeeded(std::string mat)
{
	auto lvl = _req.find(_lvl + 1)->second;

	if ( _inv.getStones(mat) < lvl.getStones(mat))
		return (lvl.getStones(mat) - _inv.getStones(mat));
	else
		return (0);
}

void zappy::AI::goAndPickup()
{
	zappy::Inventory tile = _vision.getHere();
	std::string retrieved = tile.lookForUseful(_req[_lvl + 1]);

	while (retrieved != "" && takeObject(retrieved) != false) {
		takeObject(retrieved);
		look();
		tile.lookForUseful(_req[_lvl + 1]);
	}
	PickupAllFood();
}

void zappy::AI::goAndPickup(zappy::movement mov)
{
	zappy::Inventory tile;
	std::string retrieved;

	if (mov == zappy::FORWARD)
		move(zappy::FORWARD);
	else if (mov == zappy::LEFT) {
		move(zappy::LEFT);
		move(zappy::FORWARD);
	} else if (mov == zappy::RIGHT) {
		move(zappy::RIGHT);
		move(zappy::FORWARD);
	}
	tile = _vision.getHere();
	retrieved = tile.lookForUseful(_req[_lvl + 1]);
	while (retrieved != "" && takeObject(retrieved) != false) {
		takeObject(retrieved);
		look();
		retrieved = tile.lookForUseful(_req[_lvl + 1]);
	}
	PickupAllFood();
}



zappy::movement zappy::AI::lookForUsefulClose()
{
	if (_vision.getLeft().lookForUseful(_req[_lvl + 1]) != "")
		return (zappy::movement::LEFT);
	else if (_vision.getRight().lookForUseful(_req[_lvl + 1]) != "")
		return (zappy::movement::RIGHT);
	else if (_vision.getFront().lookForUseful(_req[_lvl + 1]) != "")
		return (zappy::movement::FORWARD);
	return (zappy::movement::NOPE);
}

void zappy::AI::PickupAllOf(std::string stone)
{
	int i = _vision.getHere().getStones(stone);
	bool res = true;

	if (i > 0) {
		while (i > 0 && res) {
			res = takeObject("stone");
			i -= 1;
		}
	}
}

void zappy::AI::PickupAllOf(std::string stone, zappy::Inventory &tile)
{
	int i = tile.getStones(stone);
	bool res = true;

	if (i > 0) {
		while (i > 0 && res) {
			res = takeObject(stone);
			i -= 1;
		}
	}
}

void zappy::AI::setDownAllOf(std::string stone)
{
	int i = _reqRef[_lvl + 1].getStones(stone);
	bool res = true;

	if (i > 0) {
		while (i > 0 && res) {
			res = putObject(stone);
			i -= 1;
		}
	}
}

void zappy::AI::PickupAllFood()
{
	std::cout << "Picking up food..." << std::endl;
	int i = _vision.getHere().getFood();
	bool res = true;

	if (i > 0) {
		while (i > 0 && res) {
			res = takeObject("food");
			i -= 1;
		}
	}
}

void zappy::AI::goGetFood()
{
	_vision.lookForFood();
	move(zappy::FORWARD);
	PickupAllFood();
}
