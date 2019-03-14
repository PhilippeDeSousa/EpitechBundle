/*
** EPITECH PROJECT, 2018
** Project description
** File description:
** Description here
*/

#ifndef AI_HPP_
#define AI_HPP_

#include "Inventory.hpp"
#include "ConnectionHandler.hpp"
#include "Vision.hpp"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <cstdlib>
#include <regex>

namespace zappy {

	enum movement {
		FORWARD,
		RIGHT,
		LEFT,
		NOPE
	};

	enum AImode {
		GATHERING,
		CALLING,
		JOINING,
		FLEEING,
		IDLE
	};

	class AI {

	public:

		AI(std::string, int, const int);
		AI(std::string, const int);
		~AI();

		//AI behavior (depends on behavior mode)
		void interpret(std::string &cmd);
		void act();
		zappy::ConnectionHandler &getConnectionHandler();

		typedef void (zappy::AI::*action)();

	private:

		std::string _team;
		zappy::AImode _mode;
		int _n;
		int _dir;
		int _lvl;
		zappy::Inventory _inv;
		zappy::ConnectionHandler _cli;
		zappy::Vision _vision;
		std::map<int , zappy::Inventory> _req;
		std::map<int , zappy::Inventory> _reqRef;
		std::map<zappy::AImode, action> _behavior;

		void initAI();

		//AI Behavior:
		void gatherMaterials();
		void callAllies();
		void joinAllies();
		void flee();
		void wait();

		//commands:
		void look();
		bool takeObject(std::string object);
		bool putObject(std::string object);
		void move(zappy::movement mov);
		void inventory();
		void broadcast(std::string);
		void eject();
		bool startIncantation();

		//leveling-related functions:
		bool readyToCall(zappy::Inventory &);
		int isMaterialNeeded(std::string);
		bool lvlRequirementsMet(zappy::Inventory &);
		bool prepareTileForRitual();
		bool setRequirementsDown();
		void setDownAllOf(std::string);
		void levelUp();

		//matherial gathering-related functions:
		zappy::movement lookForUsefulClose();
		void goAndPickup(zappy::movement mov);
		void goAndPickup();
		void goGetFood();
		void PickupAllFood();
		void PickupAllOf(std::string);
		void PickupAllOf(std::string, zappy::Inventory &);

		//command interpretation
		void whereToJoin(std::string cmd);
		void beEjected(std::string cmd);

	};
};

#else

namespace zappy {
	class AI;
}

#endif /* AI_HPP_ */
