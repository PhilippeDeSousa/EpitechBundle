//
// EPITECH PROJECT, 2018
//
// File description:
//
//

#include "bollinger.hpp"

static int usage(const char *str)
{
	std::cout << "Bollinger Bands\n\nUSAGE\n\t";
        std::cout << str;
	std::cout << "[-h] period standard_dev indexes_files index_number\n\n";
	std::cout << "\tperiod\t\tnumber of indexes for the moving average\n";
	std::cout << "\tstandard_dev\tstandard deviation coefficient to apply\n";
	std::cout << "\tindexes_file\tfile containing daily indexes\n";
	std::cout << "\tindex_number\tindex number to compute moving";
	std::cout << " average and Bollinger bands\n\n";
	std::cout << "OPTIONS\n\t";
	std::cout << "-h\t\tprint the usage and quit\n";

        return 0;
}

int main(const int ac, const char **av)
{
	if (ac != 5)
                return usage(av[0]);

	try {
		Bollinger Boll(ac, av);
	} catch (Errors const &err) {
		std::cout << err.what() << std::endl;
	};
        return 0;
}
