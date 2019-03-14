/*
** EPITECH PROJECT, 2018
** Project description
** File description:
** Description here
*/

#ifndef VISION_HPP_
#define VISION_HPP_

#include <list>
#include <regex>
#include <iostream>
#include "Inventory.hpp"

namespace zappy
{

	class Vision
	{

	public:

		Vision();
		Vision(std::string input);
		~Vision() = default;

		std::vector<std::vector<Inventory>> getVision();
		int lookForFood();
		bool empty();
		zappy::Inventory getLeft();
		zappy::Inventory getRight();
		zappy::Inventory getFront();
		zappy::Inventory getHere();

	private:

		std::vector<std::vector<Inventory>> _vision;
		int _cells;

		void splitCells(std::string);
		Inventory splitPerCell(std::string);
		Inventory findMatches(Inventory, std::string, std::string);
		Inventory updateInv(Inventory, std::string);
		std::size_t howManyTiles(std::string str);
	};

}

#endif /* VISION_HPP_ */
