/*
** EPITECH PROJECT, 2018
** zappy client
** File description:
** Inventory
*/

#include "Inventory.hpp"

zappy::Inventory::Inventory(int lvl)
	: _common(false), _food(0), _players(1)
{
	_stones["linemate"] = 0;
	_stones["deraumere"] = 0;
	_stones["sibur"] = 0;
	_stones["mendiane"] = 0;
	_stones["phiras"] = 0;
	_stones["thystame"] = 0;

	switch (lvl) {
	case 2:
		_stones["linemate"] = 1;
		break;
	case 3:
		_stones["linemate"] = 1;
		_stones["deraumere"] = 1;
		_stones["sibur"] = 1;
		_players = 2;
		break;
	case 4:
		_stones["linemate"] = 2;
		_stones["phiras"] = 2;
		_stones["sibur"] = 1;
		_players = 2;
		break;
	case 5:
		_stones["linemate"] = 1;
		_stones["deraumere"] = 1;
		_stones["sibur"] = 2;
		_stones["phiras"] = 1;
		_players = 4;
		break;
	case 6:
		_stones["linemate"] = 1;
		_stones["deraumere"] = 2;
		_stones["sibur"] = 1;
		_stones["mendiane"] = 3;
		_players = 4;
		break;
	case 7:
		_stones["linemate"] = 1;
		_stones["deraumere"] = 2;
		_stones["phiras"] = 1;
		_stones["sibur"] = 3;
		_players = 4;
		break;
	case 8:
		_stones["linemate"] = 2;
		_stones["deraumere"] = 2;
		_stones["sibur"] = 2;
		_stones["mendiane"] = 2;
		_stones["phiras"] = 2;
		_stones["thystame"] = 1;
		_players = 4;
		break;
	}
}

zappy::Inventory::Inventory()
	: _common(false), _food(0), _players(0)
{
	_stones["linemate"] = 0;
	_stones["deraumere"] = 0;
	_stones["sibur"] = 0;
	_stones["mendiane"] = 0;
	_stones["phiras"] = 0;
	_stones["thystame"] = 0;
}

zappy::Inventory::Inventory(bool isCommon)
	: _common(isCommon), _food(0), _players(0)
{
	_stones["linemate"] = 0;
	_stones["deraumere"] = 0;
	_stones["sibur"] = 0;
	_stones["mendiane"] = 0;
	_stones["phiras"] = 0;
	_stones["thystame"] = 0;
}

zappy::Inventory::Inventory(bool isCommon, int food, int players,
		std::unordered_map<std::string, int>stones)
	: _common(isCommon), _food(food), _players(players), _stones(stones)
{
}

std::string zappy::Inventory::show()
{
	std::string contents;

	contents = "[linemate " + std::to_string(_stones["linemate"])
		+ ", deraumere " + std::to_string(_stones["deraumere"])
		+ ", sibur " + std::to_string(_stones["sibur"]) + ", mendiane "
		+ std::to_string(_stones["mendiane"]) + ", phiras "
		+ std::to_string(_stones["phiras"]) + ", thystame "
		+ std::to_string(_stones["thystame"]) + "]\n";
	std::cout << contents << std::endl;
	return (contents);
}

bool zappy::Inventory::isEmpty()
{
	if (_stones["linemate"] != 0 ||	_stones["deraumere"] != 0 || _stones["sibur"] != 0 ||
		_stones["mendiane"] != 0 || _stones["phiras"] != 0 || _stones["thystame"] != 0
		|| _food != 0)
		return (false);
	else
		return (true);
}

void zappy::Inventory::setEmpty()
{
	this->_food = 0;
	_stones["linemate"] = 0;
	_stones["deraumere"] = 0;
	_stones["sibur"] = 0;
	_stones["mendiane"] = 0;
	_stones["phiras"] = 0;
	_stones["thystame"] = 0;
}

bool zappy::Inventory::getCommon()
{
	return (this->_common);
}

int zappy::Inventory::getFood()
{
	return (this->_food);
}

int zappy::Inventory::getStones(std::string stone)
{
	auto res = _stones.find(stone);

	if (res != _stones.end())
		return (res->second);
	else
		return (0);
}

int zappy::Inventory::getPlayers()
{
	return (this->_players);
}

void zappy::Inventory::setCommon(bool isCommon)
{
	this->_common = isCommon;
}

void zappy::Inventory::setFood(int food)
{
	this->_food = food;
}

void zappy::Inventory::setFood()
{
	this->_food += 1;
}

void zappy::Inventory::removeFood()
{
	this->_food -= 1;
}

void zappy::Inventory::setPlayers(int players)
{
	this->_players = players;
}

void zappy::Inventory::setPlayers()
{
	this->_players += 1;
}

void zappy::Inventory::setStones(std::string stone, int qty)
{
	auto res = _stones.find(stone);

	if (res != _stones.end())
		res->second = qty;
}

void zappy::Inventory::setStones(std::string stone)
{
	auto res = _stones.find(stone);

	if (res != _stones.end())
		res->second += 1;
}

void zappy::Inventory::setStones(std::unordered_map<std::string, int> stones)
{
	_stones = stones;
}

void zappy::Inventory::removeStone(std::string stone)
{
	if (_stones.find(stone) != _stones.end())
		_stones[stone] -= 1;
}


bool zappy::Inventory::enoughMats(zappy::Inventory &inv)
{
	if (_stones.find("linemate")->second < inv._stones.find("linemate")->second ||
		_stones.find("deraumere")->second < inv._stones.find("deraumere")->second ||
		_stones.find("sibur")->second < inv._stones.find("sibur")->second ||
		_stones.find("mendiane")->second < inv._stones.find("mendiane")->second ||
		_stones.find("phiras")->second < inv._stones.find("phiras")->second ||
		_stones.find("thystame")->second < inv._stones.find("thystame")->second)
		return (false);
	else
		return (true);
}


zappy::Inventory zappy::Inventory::operator-(zappy::Inventory &inv)
{
	_food = inv._food;
	_stones.find("linemate")->second -= inv._stones.find("linemate")->second;
	_stones.find("deraumere")->second -= inv._stones.find("deraumere")->second;
	_stones.find("sibur")->second -= inv._stones.find("sibur")->second;
	_stones.find("mendiane")->second -= inv._stones.find("mendiane")->second;
	_stones.find("phiras")->second -= inv._stones.find("phiras")->second;
	_stones.find("thystame")->second -= inv._stones.find("thystame")->second;
	return (*this);
}

zappy::Inventory zappy::Inventory::operator+(zappy::Inventory &inv)
{
	_food = inv._food;
	_stones.find("linemate")->second += inv._stones.find("linemate")->second;
	_stones.find("deraumere")->second += inv._stones.find("deraumere")->second;
	_stones.find("sibur")->second += inv._stones.find("sibur")->second;
	_stones.find("mendiane")->second += inv._stones.find("mendiane")->second;
	_stones.find("phiras")->second += inv._stones.find("phiras")->second;
	_stones.find("thystame")->second += inv._stones.find("thystame")->second;
	return (*this);
}

zappy::Inventory zappy::Inventory::operator-=(zappy::Inventory &inv)
{
	_food = inv._food;
	_stones.find("linemate")->second -= inv._stones.find("linemate")->second;
	_stones.find("deraumere")->second -= inv._stones.find("deraumere")->second;
	_stones.find("sibur")->second -= inv._stones.find("sibur")->second;
	_stones.find("mendiane")->second -= inv._stones.find("mendiane")->second;
	_stones.find("phiras")->second -= inv._stones.find("phiras")->second;
	_stones.find("thystame")->second -= inv._stones.find("thystame")->second;
	return (*this);
}

zappy::Inventory zappy::Inventory::operator+=(zappy::Inventory &inv)
{
	_food = inv._food;
	_stones.find("linemate")->second += inv._stones.find("linemate")->second;
	_stones.find("deraumere")->second += inv._stones.find("deraumere")->second;
	_stones.find("sibur")->second += inv._stones.find("sibur")->second;
	_stones.find("mendiane")->second += inv._stones.find("mendiane")->second;
	_stones.find("phiras")->second += inv._stones.find("phiras")->second;
	_stones.find("thystame")->second += inv._stones.find("thystame")->second;
	return (*this);
}

zappy::Inventory zappy::Inventory::operator=(const zappy::Inventory &inv)
{
	_food = inv._food;
	_players = inv._players;
	_stones = inv._stones;
	return (*this);
}

bool zappy::Inventory::operator<(zappy::Inventory &inv)
{
	_food = inv._food;
	if (_stones.find("linemate")->second >= inv._stones.find("linemate")->second ||
		_stones.find("deraumere")->second >= inv._stones.find("deraumere")->second ||
		_stones.find("sibur")->second >= inv._stones.find("sibur")->second ||
		_stones.find("mendiane")->second >= inv._stones.find("mendiane")->second ||
		_stones.find("phiras")->second >= inv._stones.find("phiras")->second ||
		_stones.find("thystame")->second >= inv._stones.find("thystame")->second ||
		_players >= inv._players)
		return (false);
	else
		return (true);
}

bool zappy::Inventory::operator<=(zappy::Inventory &inv)
{
	_food = inv._food;
	if (_stones.find("linemate")->second > inv._stones.find("linemate")->second ||
		_stones.find("deraumere")->second > inv._stones.find("deraumere")->second ||
		_stones.find("sibur")->second > inv._stones.find("sibur")->second ||
		_stones.find("mendiane")->second > inv._stones.find("mendiane")->second ||
		_stones.find("phiras")->second > inv._stones.find("phiras")->second ||
		_stones.find("thystame")->second > inv._stones.find("thystame")->second ||
		_players > inv._players)
		return (false);
	else
		return (true);
}

bool zappy::Inventory::operator>(zappy::Inventory &inv)
{
	_food = inv._food;
	if (_stones.find("linemate")->second <= inv._stones.find("linemate")->second ||
		_stones.find("deraumere")->second <= inv._stones.find("deraumere")->second ||
		_stones.find("sibur")->second <= inv._stones.find("sibur")->second ||
		_stones.find("mendiane")->second <= inv._stones.find("mendiane")->second ||
		_stones.find("phiras")->second <= inv._stones.find("phiras")->second ||
		_stones.find("thystame")->second <= inv._stones.find("thystame")->second ||
		_players <= inv._players)
		return (false);
	else
		return (true);
}

bool zappy::Inventory::operator>=(zappy::Inventory &inv)
{
	_food = inv._food;
	if (_stones.find("linemate")->second < inv._stones.find("linemate")->second ||
			_stones.find("deraumere")->second < inv._stones.find("deraumere")->second ||
		_stones.find("sibur")->second < inv._stones.find("sibur")->second ||
		_stones.find("mendiane")->second < inv._stones.find("mendiane")->second ||
		_stones.find("phiras")->second < inv._stones.find("phiras")->second ||
		_stones.find("thystame")->second < inv._stones.find("thystame")->second ||
		_players < inv._players)
		return (false);
	else
		return (true);
}

bool zappy::Inventory::operator==(zappy::Inventory &inv)
{
	_food = inv._food;
	if (_stones.find("linemate")->second == inv._stones.find("linemate")->second &&
			_stones.find("deraumere")->second == inv._stones.find("deraumere")->second &&
		_stones.find("sibur")->second == inv._stones.find("sibur")->second &&
		_stones.find("mendiane")->second == inv._stones.find("mendiane")->second &&
		_stones.find("phiras")->second == inv._stones.find("phiras")->second &&
		_stones.find("thystame")->second == inv._stones.find("thystame")->second &&
		_players >= inv._players)
		return (true);
	else
		return (false);
}

std::string zappy::Inventory::lookForUseful(zappy::Inventory &goals)
{
	if (_stones.find("linemate")->second <= goals._stones.find("linemate")->second &&
			_stones.find("linemate")->second > 0)
		return ("linemate");
	else if (_stones.find("deraumere")->second <= goals._stones.find("deraumere")->second &&
			_stones.find("deraumere")->second > 0)
		return ("deraumere");
	else if (_stones.find("sibur")->second <= goals._stones.find("sibur")->second  &&
			_stones.find("sibur")->second > 0)
		return ("sibur");
	else if (_stones.find("mendiane")->second <= goals._stones.find("mendiane")->second &&
			_stones.find("mendiane")->second > 0)
		return ("mendiane");
	else if (_stones.find("phiras")->second <= goals._stones.find("phiras")->second &&
			_stones.find("phiras")->second > 0)
		return ("phiras");
	else if (_stones.find("thystame")->second <= goals._stones.find("thystame")->second &&
			_stones.find("thystame")->second > 0)
		return ("thystame");
	return ("");
}
