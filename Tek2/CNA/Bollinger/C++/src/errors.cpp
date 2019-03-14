//
// EPITECH PROJECT, 2018
// Bollinger
// File description:
// Errors.cpp
//

#include "errors.hpp"

Errors::Errors(const std::string &message) throw()
	: Message(message)
{}

Errors::~Errors()
{}

const char *Errors::what() const throw()
{
	return Message.data();
}
