/*
 ** EPITECH PROJECT, 2018
 ** Project description
 ** File description:
 ** Description here
 */

#include "Client.hpp"
#include "Errors.hpp"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <memory.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <poll.h>
#include <wait.h>
#include <errno.h>
#include <getopt.h>

zappy::Client::Client(int _ac, char **av)
:	ArgCount(_ac), Machine("127.0.0.1"), _maxEvents(10), _efd(0)
{
	struct epoll_event ev;

	_efd = epoll_create(_maxEvents);
	if (_efd < 0)
		throw (Exceptions("Epoll create error\n"));
	_events = ev;
	MyGetopt(_ac, av);
	if (Team == "" || _port == 0)
		throw (Exceptions(std::string(av[0]) + RET_USAGE +
		USAGE_PORT + USAGE_NAME + USAGE_MACHINE + USAGE_LOCALHOST));
	createFirstClient();
}

zappy::Client::~Client() noexcept
{
}

int zappy::Client::IsNum(char *num)
{
	char *ptr = num;

	while (*ptr) {
		if (!isdigit(*ptr))
			return 0;
		++ptr;
	}
	return atoi(num);
}

void zappy::Client::SwitchCase(int c)
{
	switch (c) {
		case 'p':
			_port = IsNum(optarg);
			break;
		case 'h':
			Machine = optarg;
			break;
		case 'n' :
			Team = optarg;
			break;
	}
}

void zappy::Client::MyGetopt(int argc, char **argv)
{
	int c;

	while (1)
	{
		static struct option long_options[] =
			{
				{"_port", required_argument, 0, 'p'},
				{"name", required_argument, 0, 'n'},
				{"machine", required_argument, 0, 'h'},
				{0, 0, 0, 0}
			};
		int option_index = 0;
		c = getopt_long(argc, argv, "p:n:h:",
			long_options, &option_index);
		if (c == -1)
			break;
		SwitchCase(c);
	}
}

void zappy::Client::GetServer()
{
	int sockfd = 0;
	struct sockaddr_in s_ad;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if ((sockfd < 0))
		throw(Exceptions("Socket error\n"));
	memset(&s_ad, '0', sizeof(s_ad));
	s_ad.sin_family = AF_INET;
	s_ad.sin_port = htons(_port);
	if (inet_pton(AF_INET, Machine.c_str(), &s_ad.sin_addr) <= 0)
		throw(Exceptions("Inet error\n"));
	if (connect(sockfd, (struct sockaddr *)&s_ad, sizeof(s_ad)) < 0)
		throw(Exceptions("Connect error\n"));
	_serverFd = sockfd;
	_events.data.fd = _serverFd;
	_events.events = EPOLLIN | EPOLLET;
	if (epoll_ctl(_efd, EPOLL_CTL_ADD, _serverFd, &_events) == -1)
		throw(Exceptions("Epoll error\n"));
}

void zappy::Client::waitForChildProcesses()
{
	while (true) {
		int status;
		pid_t done = wait(&status);
		if (done == -1) {
			if (errno == ECHILD) break;
		} else {
			if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
				std::cerr << "pid " << done << " failed" << std::endl;
				exit(1);
			}
		}
	}
}

void zappy::Client::hatch()
{
}

void zappy::Client::createFirstClient()
{
	GetServer();
	if (_serverFd <= 0)
		throw Exceptions("Socket error.\n");

	zappy::AI ai(Team, _serverFd);
	std::string answer = "ok\n";
	pid_t pid = -1;

	while (answer == "ok\n") {
		ai.getConnectionHandler().sendRequest("Fork\n");
		answer = ai.getConnectionHandler().getAnswer();
		if (answer == "ok\n")
			pid = layEgg();
		else {
			Epoll(ai);
			waitForChildProcesses();
		}
		if (pid == 0) {
			GetServer();
			Epoll();
			exit(0);
		}
	}
}

pid_t zappy::Client::layEgg()
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
		throw(Exceptions("Can't create child process\n"));
	return (pid);
}

void zappy::Client::Epoll(zappy::AI &ai)
{
	std::string input;

	ai.act();
	while (1) {
		epoll_wait(_efd, &_events, _maxEvents, 5);
		if (_events.events & EPOLLERR)
			throw(Exceptions("Epoll error\n"));
		else if (_events.events & EPOLLIN)  {
			input = receive();
			if (input == "\n" || input == "")
				ai.interpret(input);
			ai.act();
		} else
			ai.act();

	}
}

void zappy::Client::Epoll()
{
	zappy::AI ai(Team, _serverFd);
	std::string input;

	ai.act();
	while (1) {
		epoll_wait(_efd, &_events, _maxEvents, 0);
		if (_events.events & EPOLLERR)
			throw(Exceptions("Epoll error\n"));
		else if (_events.events & EPOLLIN)  {
			input = receive();
			if (input == "\n" || input == "")
				ai.interpret(input);
			ai.act();
		} else
			ai.act();

	}
}

std::string zappy::Client::receive()
{
	std::string input;
	struct pollfd pfd = {STDIN_FILENO, POLLIN, 0};
	int ret = 0;

	ret = poll(&pfd, 1, 20);
	if (ret == 1)
		std::getline(std::cin, input);
	else if(ret == -1)
	     	std::cout << "Error: " << strerror(errno) << std::endl;
	if (input != "" && input != "\n")
		std::cout << "Received: " << input << std::endl;
	return (input);
}
