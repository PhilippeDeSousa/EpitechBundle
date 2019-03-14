//
// EPITECH PROJECT, 2018
// Bollinger
// File description:
// Include
//

#ifndef ERRORS_HPP
# define ERRORS_HPP

# include <iostream>
# include <string>
# include <vector>
# include <fstream>

class Errors {
public:
	Errors(const std::string &message) throw();
	~Errors();
	const char *what() const throw();
private:
	std::string Message;
};

#endif /* !BOLLINGER_HPP */
