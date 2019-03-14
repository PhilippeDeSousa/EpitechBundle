/*
** EPITECH PROJECT, 2018
** Project description
** File description:
** Description here
*/

#include "Vision.hpp"

zappy::Vision::Vision()
	: _cells(1)
{
}

zappy::Vision::Vision(std::string str)
	: _cells(1)
{
	std::string delimiter = ",";
	std::string strCell;
	std::vector<Inventory> list;
	size_t last = 0;
	size_t next = 0;
	int i = 0;

	while ((next = str.find(delimiter, last)) != std::string::npos) {
		strCell = std::string(str.substr(last, next - last));
		if (i < _cells)
			list.push_back(splitPerCell(strCell));
		else  {
			_vision.push_back(list);
			list = std::vector<Inventory>();
			i = 0;
			list.push_back(splitPerCell(strCell));
			_cells += 2;
		}
		last = next + 1;
		i += 1;
	}
	strCell = std::string(str.substr(last));
	list.push_back(splitPerCell(strCell));
	_vision.push_back(list);
}

bool zappy::Vision::empty()
{
	if (_vision.empty())
		return (true);
	else
		return (false);
}

zappy::Inventory zappy::Vision::updateInv(Inventory tile, std::string match)
{
	if (match == "player")
		tile.setPlayers();
	else if (match == "food")
		tile.setFood();
	else
		tile.setStones(match);
	return (tile);
}

zappy::Inventory zappy::Vision::findMatches(Inventory tile, std::string str,
		std::string strRegex)
{
	std::regex reg(strRegex);
	std::sregex_iterator it(str.begin(), str.end(), reg);
	std::sregex_iterator end;

	while(it != end) {
		for (std::size_t i = 0; i < it->size(); ++i) {
			tile = updateInv(tile, (*it)[i]);
		}
		it++;
	}
	return (tile);
}

zappy::Inventory zappy::Vision::splitPerCell(std::string str)
{
	zappy::Inventory tile;

	tile = findMatches(tile, str, "food");
	tile = findMatches(tile, str, "player");
	tile = findMatches(tile, str, "linemate");
	tile = findMatches(tile, str, "deraumere");
	tile = findMatches(tile, str, "sibur");
	tile = findMatches(tile, str, "mendiane");
	tile = findMatches(tile, str, "phiras");
	tile = findMatches(tile, str, "thystame");
	return (tile);
}

int zappy::Vision::lookForFood()
{
	return (0);
}

std::size_t zappy::Vision::howManyTiles(std::string str)
{
	std::size_t n = std::count(str.begin(), str.end(), ',') + 1;
	return (n);
}

std::vector<std::vector<zappy::Inventory>> zappy::Vision::getVision()
{
	return (this->_vision);
}

zappy::Inventory zappy::Vision::getHere()
{
	if (_vision.empty())
		std::cout << "empty vector !" << std::endl;
	return (_vision[0][0]);
}

zappy::Inventory zappy::Vision::getLeft()
{
	return (_vision[1][0]);
}

zappy::Inventory zappy::Vision::getFront()
{
	return (_vision[1][1]);
}

zappy::Inventory zappy::Vision::getRight()
{

	return (_vision[1][2]);
}
