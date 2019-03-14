//
// EPITECH PROJECT, 2018
//
// File description:
//
//

#ifndef ERRORS_HPP
# define ERRORS_HPP

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

class InputException : public Exceptions
{
public:
        InputException(const std::string &) throw();
        ~InputException();
};

class SyntaxException : public Exceptions
{
public:
        SyntaxException(const std::string &) throw();
        ~SyntaxException();
};

class FileException : public Exceptions
{
public:
        FileException(const std::string &) throw();
        ~FileException();
};

class PinException : public Exceptions
{
public:
        PinException(const std::string &) throw();
        ~PinException();
};

class CommandException : public Exceptions
{
public:
        CommandException(const std::string &) throw();
        ~CommandException();
};

#endif /* !ERRORS_HPP */
