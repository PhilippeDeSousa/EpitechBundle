/*
 ** EPITECH PROJECT, 2018
 ** Project description
 ** File description:
 ** Description here
 */

#include "Client.hpp"
#include "Errors.hpp"
#include "Graphic.hpp"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <memory.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <getopt.h>

zappy::Client::Client(int _ac, char **av)
:	ArgCount(_ac), Machine("127.0.0.1")
{
	MyGetopt(_ac, av);
	if (Port == 0)
		throw (Exceptions(std::string(av[0]) + RET_USAGE +
		USAGE_PORT));
	HandleClient();
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
			Port = IsNum(optarg);
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
				{"port", required_argument, 0, 'p'},
				{0, 0, 0, 0}
			};
		int option_index = 0;
		c = getopt_long(argc, argv, "p:",
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
	s_ad.sin_port = htons(Port);
	if (inet_pton(AF_INET, Machine.c_str(), &s_ad.sin_addr) <= 0)
		throw(Exceptions("Inet error\n"));
	if (connect(sockfd, (struct sockaddr *)&s_ad, sizeof(s_ad)) < 0)
		throw(Exceptions("Connect error\n"));
	Server_fd = sockfd;
}

void zappy::Client::FirstConnection()
{
	std::string Answer;
	std::string Str;

	Answer = ReadLine();
	if (Answer.empty())
		exit(0);
	dprintf(Server_fd, "GRAPHIC\n");
}

char zappy::Client::GetBuff()
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

	return c;
}

std::string zappy::Client::ReadLine()
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
	return line;
}

int zappy::Client::GetServerfd()
{
	return Server_fd;
}

void zappy::Client::HandleClient()
{
	Graphic *game = new Graphic;

	GetServer();
	if (Server_fd <= 0)
		throw (Exceptions("Socket error.\n"));
	FirstConnection();
	game->gameLoop(this);
}
