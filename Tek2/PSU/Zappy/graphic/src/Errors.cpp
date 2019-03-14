//
// EPITECH PROJECT, 2018
//
// File description:
//
//

#include "Errors.hpp"

Exceptions::Exceptions(const std::string &message) throw()
        : Message(message)
{
}

Exceptions::~Exceptions()
{}

const char *Exceptions::what(void) const throw()
{
        return (Message.data());
}
