//
// EPITECH PROJECT, 2018
// zappy
// File description:
// client errors
//

#ifndef ERRORS_HPP
# define ERRORS_HPP

# include "Usage.hpp"
# include <iostream>
# include <string>
# include <vector>
# include <fstream>

class Exceptions : public std::exception
{

public:
	Exceptions(const std::string &) throw();
	~Exceptions();
	const char *what(void) const throw();

private:
	std::string Message;
};

#endif /* !ERRORS_HPP */
