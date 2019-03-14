/*
** EPITECH PROJECT, 2018
** Project description
** File description:
** Description here
*/

#include "AI.hpp"

void zappy::AI::act()
{
	std::cout << "New action loop\n" << std::endl;
	auto res = _behavior.find(_mode);
	if (res != _behavior.end())
		((*this).*res->second)();
}

void zappy::AI::gatherMaterials()
{
	std::string vision;
	zappy::movement mov;
	int dir;

	std::cout << "AI in gathering mode\n";
	look();
	goAndPickup();
	mov = lookForUsefulClose();
	if (mov != zappy::movement::NOPE)
		goAndPickup(mov);
	else {
		goAndPickup();
		dir = (std::rand() % 3 + 1);
		if (dir == 1)
			move(zappy::LEFT);
		else if (dir == 2)
			move(zappy::RIGHT);
		move(zappy::FORWARD);
	}
	if (readyToCall(_inv))
		_mode = zappy::AImode::CALLING;
}

void zappy::AI::callAllies()
{
	std::cout << "AI calling allies..." << std::endl;
	look();
	if (_inv.getFood() < 5 && _lvl > 1)
		goGetFood();
	if (_lvl > 1)
		broadcast("Come here, " + _team + " of level " + std::to_string(_lvl));
	look();
	if (_inv >= _reqRef[_lvl + 1]) {
		prepareTileForRitual();
		if (startIncantation() == false) {
			std::cout << "Incantation failed, preparing to retry...\n";
			_mode = zappy::AImode::GATHERING;
		}
	}
}

void zappy::AI::joinAllies()
{
	std::cout << "AI joining allies..." << std::endl;
	look();
	goAndPickup();
	PickupAllFood();
	move(zappy::FORWARD);
	_mode = GATHERING;
}

void zappy::AI::flee()
{
	std::cout << "AI fleeing..." << std::endl;
	_mode = zappy::IDLE;
}

void zappy::AI::wait()
{
	std::cout << "AI waiting for allies..." << std::endl;
	_mode = zappy::GATHERING;
}
