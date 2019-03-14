/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** main
*/

#include <exception>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Errors.hpp"
#include "Client.hpp"

int main(int ac, char **av)
{
	std::srand(std::time(nullptr));
	try {
		zappy::Client Cl(ac, av);
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
}
