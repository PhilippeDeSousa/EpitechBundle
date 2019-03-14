/*
** EPITECH PROJECT, 2018
** Project description
** File description:
** Description here
*/

#include "AI.hpp"

void zappy::AI::interpret(std::string &cmd)
{
	std::smatch match;

	if (cmd == "dead\n")
		exit(0);
	if (std::regex_search(cmd, match, std::regex("Come here, " + _team))) {
		whereToJoin(cmd);
	} else if (std::regex_search(cmd, match, std::regex("eject")))
		beEjected(cmd);
	else if (std::regex_search(cmd, match, std::regex("Elevation underway")))
		levelUp();
}

void zappy::AI::beEjected(std::string cmd)
{
	int i = 1;

	_dir = std::atoi(cmd.c_str());
	while (i < _dir) {
		move(zappy::LEFT);
		i += 1;
	}
	move(zappy::FORWARD);
}

void zappy::AI::whereToJoin(std::string cmd)
{
	int i = 1;

	std::string strdir = cmd.substr(0, cmd.find(", "));
	_dir = std::atoi(strdir.c_str());
	_mode = zappy::AImode::JOINING;
	while (i < _dir) {
		move(zappy::LEFT);
		i += 1;
	}
	move(zappy::FORWARD);
}
