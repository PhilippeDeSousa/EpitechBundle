/*
** EPITECH PROJECT, 2018
** Project description
** File description:
** Description here
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include <vector>
#include <iostream>
#include "Usage.hpp"
#include "Errors.hpp"
#include "Graphic.hpp"

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
		void HandleClient();
		char GetBuff();
		std::string ReadLine();
		void FirstConnection();
		int GetServerfd();

	private:
		const int ArgCount;
		int Server_fd;
		int Port = 0;
		std::string Team = "";
		std::string Machine;
		std::vector<std::string> Args;
	};

}

#else

namespace zappy {
	class Client;
}

#endif /* CLIENT_HPP_ */
