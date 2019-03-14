/*
** EPITECH PROJECT, 2018
** Project description
** File description:
** Description here
*/

#include "AI.hpp"

void zappy::AI::look()
{
	std::string str;

	_cli.sendRequest("Look\n");
	str = _cli.getAnswer();
	_vision = zappy::Vision(str);
}

void zappy::AI::move(zappy::movement mov)
{
	if (mov == FORWARD) {
		_cli.sendRequest("Forward\n");
	} else if (mov == RIGHT)
		_cli.sendRequest("Right\n");
	else if (mov == LEFT)
		_cli.sendRequest("Left\n");
	else
		return ;
	_cli.getAnswer();
}

void zappy::AI::inventory()
{
	_cli.sendRequest("Inventory\n");
	_cli.getAnswer();
}

bool zappy::AI::takeObject(std::string object)
{
	if (object != "food")
		std::cout << "Picking up: " << object << std::endl;
	_cli.sendRequest("Take " + object + "\n");
	if (_cli.getAnswer() == "ok\n") {
		if (object != "food") {
			_inv.setStones(object);
			if (_req[_lvl + 1].getStones(object) > 0)
				_req[_lvl + 1].removeStone(object);
		} else
			_inv.setFood();
		return (true);
	}
	return (false);
}

bool zappy::AI::putObject(std::string object)
{
	_cli.sendRequest("Set " + object + "\n");
	if (_cli.getAnswer() == "ok\n") {
		if (object != "food")
			_inv.removeStone(object);
		else
			_inv.removeFood();
		return (true);
	}
	return (false);
}

void zappy::AI::broadcast(std::string msg)
{
	_cli.sendRequest("Broadcast " + msg + "\n");
	_cli.getAnswer();
}

void zappy::AI::eject()
{
	_cli.sendRequest("Eject\n");
	_cli.getAnswer();
}
