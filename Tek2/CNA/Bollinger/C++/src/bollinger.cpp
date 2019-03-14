//
// EPITECH PROJECT, 2018
// Bollinger
// File description:
// Bollinger.cpp
//

#include "bollinger.hpp"
#include <iomanip>
#include <algorithm>

Bollinger::Bollinger(const int ac, const char **av)
	: argCount(ac), Filename(av[3])
{
	std::ifstream file;
	file.open(Filename, std::ifstream::in);
	if (!file)
		throw (Errors("File " + Filename + " does not exist"));
	else {
		std::string s;
		while (std::getline(file, s))
			File.push_back(s);
		setArgs(av[1], av[2], av[4]);
	}
	printInput();
	setMovingAverage();
	setStandardDeviation();
	setHighBand();
	setLowBand();
	printOutput();
}

Bollinger::~Bollinger()
{}

void Bollinger::setMovingAverage()
{
	double _average = 0;
	MA = 0;
	for (size_t i = Index - Period; i < Index; i++) {
		std::stringstream tmp(File[i]);
		tmp >> _average;
		MA += _average;
	}
	MA /= Period;
}

void Bollinger::setStandardDeviation()
{
	float _dev = 0;
	float sum = 0;
	SD = 0;
	for (size_t i = Index - Period; i < Index; i++) {
		std::stringstream tmp(File[i]);
		tmp >>  _dev;
		_dev = pow((_dev - MA), 2);
		sum += _dev;
	}
	sum /= Period;
	SD = sqrt(sum);
}

void Bollinger::setHighBand()
{
	BMax = MA + (SD * Coef);
}

void Bollinger::setLowBand()
{
	BMin = MA - (SD * Coef);
}

void Bollinger::setArgs(const std::string _period, const std::string _coef,
			const std::string _index)
{
	std::stringstream tmpPer(_period);
	tmpPer >> Period;
	std::stringstream tmpCoef(_coef);
	tmpCoef >> Coef;
	std::stringstream tmpInd(_index);
	tmpInd >> Index;
	Index += 1;
	if (Period < 1 || Coef < 1 || Index > File.size())
		throw (Errors("Wrong inputs"));
}

void Bollinger::printInput()
{
	std::cout << "INPUT\nIndex: ";
	std::cout << Index - 1 << std::endl;
	std::cout << "Period ";
	std::cout << Period << std::endl;
	std::cout << "SD_coef: ";
	std::cout << std::fixed << std::setprecision(2) << Coef << std::endl;
}

void Bollinger::printOutput()
{
	int i = 1;
	int nb = 0;
	while (SD < 0.01 / i) {
		nb += 1;
		std::cout << std::fixed << std::setprecision(2 + nb);
		i += 10;
	}
	std::cout << "\nOUTPUT\nMA: ";
	std::cout << MA << std::endl;
	std::cout << "SD: ";
	std::cout << SD << std::endl;
	std::cout << "B+: ";
	std::cout << BMax << std::endl;
	std::cout << "B-: ";
	std::cout << BMin << std::endl;
        
}
