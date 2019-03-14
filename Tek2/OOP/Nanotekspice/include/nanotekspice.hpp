//
// EPITECH PROJECT, 2018
//
// File description:
//
//

#ifndef NANOTEKSPICE_HPP
# define NANOTEKSPICE_HPP

# include "config.hpp"
# include <iostream>
# include <algorithm>
# include <string>

class Nanotekspice
{
public:
        static bool sigVal;
public:
        Nanotekspice(const std::string &, const int, const char **);
        ~Nanotekspice();
        int getArgNb() const;
        const char **getArgTab() const;
        void setValue(std::string);
        void Display();
        void Exec();
        void Simulate();
        void Dump();
        void Loop();
private:
        const int argCount;
        const char **tabArg;
        Config *Conf;

};

void sigHandler(int);

#endif /* !NANOTEKSPICE_HPP */
