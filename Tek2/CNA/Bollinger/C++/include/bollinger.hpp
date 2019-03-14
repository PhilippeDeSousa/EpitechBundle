//
// EPITECH PROJECT, 2018
// Bollinger
// File description:
// Include
//

#ifndef BOLLINGER_HPP
# define BOLLINGER_HPP

# include <iostream>
# include <vector>
# include <sstream>
# include "errors.hpp"
# include <math.h>

class Bollinger {
public:
	Bollinger(const int ac, const char **);
	~Bollinger();
	void setArgs(const std::string, const std::string,
		     const std::string);
	void printInput();
	void printOutput();
	void setMovingAverage();
	void setStandardDeviation();
	void setHighBand();
	void setLowBand();
private:
	const int argCount;
	std::size_t Period;
	float Coef;
	std::string Filename;
	std::size_t Index;
	double MA;
	double SD;
	double BMax;
	double BMin;
	std::vector <std::string> File;
};

#endif /* !BOLLINGER_HPP */
