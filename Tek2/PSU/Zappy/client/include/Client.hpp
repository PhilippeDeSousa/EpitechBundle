/*
** EPITECH PROJECT, 2018
** Project description
** File description:
** Description here
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include <netinet/in.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <netdb.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <stdlib.h>

#include <vector>
#include <iostream>

#include "Usage.hpp"
#include "Errors.hpp"
#include "AI.hpp"

namespace zappy
{

	class Client
	{

	public:
		Client(int, char **);
		~Client() noexcept;
		void MyGetopt(int, char **);
		void SwitchCase(int);
		int IsNum(char *);
		void CheckArgs();
		void GetServer();

	private:

		const int ArgCount;
		int _serverFd;
		int _port = 0;
		std::string Team = "";
		std::string Machine;
		std::vector<std::string> Args;
		int _maxEvents;
		int _efd;
		struct epoll_event _events;
		struct sockaddr_in addr;

		void Epoll();
		void Epoll(zappy::AI &ai);
		std::string receive();
		void hatch();
		void createFirstClient();
		pid_t layEgg();
		void waitForChildProcesses();
	};

}

#else

namespace zappy {
	class Client;
}

#endif /* CLIENT_HPP_ */
