/*
 ** EPITECH PROJECT, 2018
 ** Project description
 ** File description:
 ** Description here
 */

#ifndef CONNECTIONHANDLER_HPP_
#define CONNECTIONHANDLER_HPP_

#include "Usage.hpp"
#include "Errors.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <unistd.h>

namespace zappy
{

	class ConnectionHandler
	{

	public:

		ConnectionHandler(const int, std::string);
		~ConnectionHandler();

		void sendRequest(std::string);
		std::string getAnswer();

	private:

		void receive();
		bool processConnection();
		void EventLoop();
		void HandleAi();
		void FirstConnection();
		std::string ReadLine();
		char GetBuff();

		int AvailableSlots;
		std::string _connectNumber;
		const int Server_fd;
		std::string _teamName;
		int _x;
		int _y;
		std::pair<std::string, std::string> _world;
		std::string _answer;
	};

}

#endif /* CONNECTIONHANDLER_HPP_ */
