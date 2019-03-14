/*
** EPITECH PROJECT, 2018
** Project description
** File description:
** Description here
*/

#include "AI.hpp"

zappy::AI::AI(std::string teamName, int n, const int servFd)
	: _team(teamName), _mode(zappy::GATHERING), _n(n),
	  _dir(0), _lvl(1), _cli(ConnectionHandler(servFd, teamName))
{
	initAI();
}

zappy::AI::AI(std::string teamName, const int servFd)
	: _team(teamName), _mode(zappy::GATHERING), _n(0),
	  _dir(0), _lvl(1), _cli(ConnectionHandler(servFd, teamName))
{
	initAI();
}

zappy::AI::~AI()
{
	std::cout << "I'm dead!" << std::endl;
}


void zappy::AI::initAI()
{
	std::cout << "A new player is born!\n";
	this->_inv = Inventory();
	_inv.setPlayers(1);

	//AI behavior mode and associated functions
	_behavior.insert(std::make_pair(zappy::GATHERING, &AI::gatherMaterials));
	_behavior.insert(std::make_pair(zappy::CALLING, &AI::callAllies));
	_behavior.insert(std::make_pair(zappy::JOINING, &AI::joinAllies));
	_behavior.insert(std::make_pair(zappy::FLEEING, &AI::flee));
	_behavior.insert(std::make_pair(zappy::IDLE, &AI::wait));

	//required materials for each level
	for (int i = 2; i < 9; i++) {
		_req[i] = zappy::Inventory(i);
		_reqRef[i] = zappy::Inventory(i);
	}
}

zappy::ConnectionHandler &zappy::AI::getConnectionHandler()
{
	return (_cli);
}
