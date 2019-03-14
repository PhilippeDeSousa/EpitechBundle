//
// EPITECH PROJECT, 2018
//
// File description:
//
//

#include "errors.hpp"

Exceptions::Exceptions(const std::string &message) throw()
        : Message(message)
{}

Exceptions::~Exceptions()
{}

const char *Exceptions::what(void) const throw()
{
        return (Message.data());
}

InputException::InputException(const std::string &message) throw()
        : Exceptions(message)
{}

InputException::~InputException()
{}

SyntaxException::SyntaxException(const std::string &message) throw()
        : Exceptions(message)
{}

SyntaxException::~SyntaxException()
{}

FileException::FileException(const std::string &message) throw()
        : Exceptions(message)
{}

FileException::~FileException()
{}

PinException::PinException(const std::string &message) throw()
        : Exceptions(message)
{}

PinException::~PinException()
{}

CommandException::CommandException(const std::string &message) throw()
        : Exceptions(message)
{}

CommandException::~CommandException()
{}
