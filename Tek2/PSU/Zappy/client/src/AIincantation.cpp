/*
** EPITECH PROJECT, 2018
** Project description
** File description:
** Description here
*/

#include "AI.hpp"

bool zappy::AI::startIncantation()
{
	look();
	std::cout << "Starting elevation incantation\n";
	_cli.sendRequest("Incantation\n");
	if (_cli.getAnswer() != "ko\n") {
		levelUp();
		look();
		_mode = zappy::GATHERING;
		return (true);
	} else
		return (false);
}

bool zappy::AI::readyToCall(zappy::Inventory &inv)
{
	auto lvl = _reqRef.find(_lvl + 1);
	if (lvl != _reqRef.end()) {
		if (inv.enoughMats(lvl->second) == true)
			return (true);
	}
	return (false);
}

bool zappy::AI::lvlRequirementsMet(zappy::Inventory &inv)
{
	auto lvl = _reqRef.find(_lvl + 1);
	if (lvl != _reqRef.end()) {
		if (inv >= lvl->second)
			return (true);
	}
	return (false);
}

bool zappy::AI::prepareTileForRitual()
{
	zappy::Inventory tile = _vision.getHere();

	PickupAllOf("linemate", tile);
	PickupAllOf("deraumere", tile);
	PickupAllOf("sibur", tile);
	PickupAllOf("mendiane", tile);
	PickupAllOf("phiras", tile);
	PickupAllOf("thystame", tile);
	PickupAllFood();
	look();
	if (_vision.getHere().isEmpty() == true)
		std::cout << "Current tile emptied for ritual !" << std::endl;
	else {
		std::cout << "Current tile emptied for ritual !" << std::endl;
		return (false);
	}
	return (setRequirementsDown());
}

bool zappy::AI::setRequirementsDown()
{
	setDownAllOf("linemate");
	setDownAllOf("deraumere");
	setDownAllOf("sibur");
	setDownAllOf("mendiane");
	setDownAllOf("phiras");
	setDownAllOf("thystame");
	look();
	if (_vision.getHere() == _reqRef[_lvl + 1])
		return (true);
	else
		return (false);
}

void zappy::AI::levelUp()
{
	this->_lvl += 1;
	std::cout << "Leveled up! New level: " << std::to_string(_lvl) << std::endl;
}
