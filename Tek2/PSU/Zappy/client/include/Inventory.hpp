/*
** EPITECH PROJECT, 2018
** Project description
** File description:
** Description here
*/

#ifndef INVENTORY_HPP_
#define INVENTORY_HPP_

#include <unordered_map>
#include <vector>
#include <iostream>
#include <list>

namespace zappy
{

	class Inventory
	{

	public:

		Inventory();
		Inventory(int lvl);
		Inventory(bool isCommon);
		Inventory(bool, int, int, std::unordered_map<std::string, int>);
		~Inventory() = default;

		void setEmpty();
		std::string show();

		bool getCommon();
		bool isEmpty();
		int getFood();
		int getPlayers();
		int getStones(std::string stone);
		std::unordered_map<std::string, int> getStones();

		void setCommon(bool isCommon);
		void setFood(int food);
		void setFood();
		void setPlayers(int players);
		void setPlayers();
		void setStones(std::string stone);
		void setStones(std::string stone, int qty);
		void setStones(std::unordered_map<std::string, int> stones);
		void removeStone(std::string stone);
		void removeFood();

		std::string lookForUseful(zappy::Inventory &goals);
		bool enoughMats(zappy::Inventory &goals);

		zappy::Inventory operator-(zappy::Inventory &inv);
		zappy::Inventory operator+(zappy::Inventory &inv);
		zappy::Inventory operator-=(zappy::Inventory &inv);
		zappy::Inventory operator+=(zappy::Inventory &inv);
		zappy::Inventory operator=(const zappy::Inventory &inv);
		bool operator<(zappy::Inventory &inv);
		bool operator<=(zappy::Inventory &inv);
		bool operator>(zappy::Inventory &inv);
		bool operator>=(zappy::Inventory &inv);
		bool operator==(zappy::Inventory &inv);

	private:

		bool _common;
		int _food;
		int _players;
		std::unordered_map<std::string, int> _stones;
	};

}

#else

namespace zappy {
	class Inventory;
}

#endif /* INVENTORY_HPP_ */

