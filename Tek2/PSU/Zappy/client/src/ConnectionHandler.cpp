/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Connection Handler
*/

#include "ConnectionHandler.hpp"
#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>

static bool SigExit = false;

zappy::ConnectionHandler::ConnectionHandler(const int _serverfd, std::string _team)
:	Server_fd(_serverfd), _teamName(_team)
{
	FirstConnection();
}

zappy::ConnectionHandler::~ConnectionHandler() noexcept
{
}

static void sig_handler(int sig)
{
	SigExit = true;
	(void)sig;
}

void zappy::ConnectionHandler::FirstConnection()
{
	std::string Answer;
	std::string Str;

	Answer = ReadLine();
	if (Answer.empty() || SigExit)
		throw(Exceptions("Welcome wasn't received, exiting..."));
	dprintf(Server_fd, "%s\n", _teamName.c_str());
	_connectNumber = ReadLine();
	if (_connectNumber.find("ko") != std::string::npos)
		throw(Exceptions(_connectNumber));
	Str = ReadLine();
	auto pos = Str.find(' ');
	if (pos == std::string::npos)
		throw(Exceptions("Map error, exiting..."));
	_world = std::make_pair(Str.substr(0, pos), Str.substr(pos + 1));
}

void zappy::ConnectionHandler::sendRequest(std::string request)
{
	std::string answer;

	//std::cout << "Sent: " << request;
	dprintf(Server_fd, "%s", request.c_str());
	if (!(answer = ReadLine()).empty()) {
		while (answer.back() != '\n')
			answer += ReadLine();
		if (answer == "dead") {
			std::cout << "Ow, I'm dead!" << std::endl;
			exit(0);
		}
		_answer = answer;
	}
}

std::string zappy::ConnectionHandler::getAnswer()
{
	//std::cout << "Received: " << _answer;
	return (_answer);
}

void zappy::ConnectionHandler::HandleAi()
{
	std::string request;
	std::string answer;
	struct sigaction sig_act {};

	sig_act.sa_handler = sig_handler;
	sigaction(SIGINT, &sig_act, NULL);
	while (std::getline(std::cin, request)) {
		if (request.empty() || SigExit)
			break;
		dprintf(Server_fd, "%s\n", request.c_str());
		if (!(answer = ReadLine()).empty() && !SigExit) {
			while (answer.back() != '\n')
				answer += ReadLine();
			if (answer == "dead")
				break;
			std::cout << answer;
		}
	}
	std::cout << "\nI'm out, peace!\n";
	close(Server_fd);
}

char zappy::ConnectionHandler::GetBuff()
{
	static char buff[1];
	static char *ptr;
	static int rd_val = 0;
	char c;

	if (rd_val == 0) {
		rd_val = read(Server_fd, buff, 1);
		if (rd_val == 0)
			return (0);
		ptr = buff;
	}
	c = *ptr;
	ptr += 1;
	rd_val -= 1;

	return (c);
}

std::string zappy::ConnectionHandler::ReadLine()
{
	char buff;
	std::string line;

	buff = GetBuff();
	for (int i = 0; buff && buff != '\n'; i++) {
		if (buff == '\0')
			return (NULL);
		line += buff;
		buff = GetBuff();
	}
	line += buff;
	return (line);
}
