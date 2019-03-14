//
// EPITECH PROJECT, 2018
//
// File description:
//
//

#include "nanotekspice.hpp"
#include <sstream>

static int usage(const char *str)
{
        std::cout << "Usage: ";
        std::cout << str;
        std::cout << " file.nts" << std::endl;

        return 0;
}

int main(const int ac, const char **av)
{
        if (ac < 2)
                return usage(av[0]);

        try  {
                Nanotekspice Nano(av[1], ac, av);
        }
        catch (Exceptions const &e) {
                std::cout << e.what() << std::endl;
        }

        return 0;
}
