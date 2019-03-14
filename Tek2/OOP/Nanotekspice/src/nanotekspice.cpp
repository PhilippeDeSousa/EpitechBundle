//
// EPITECH PROJECT, 2018
//
// File description:
//
//

#include "nanotekspice.hpp"
#include "signal.h"

bool Nanotekspice::sigVal = true;

Nanotekspice::Nanotekspice(const std::string &filename, const int ac,
                const char **av)
        : argCount(ac), tabArg(av)
{
        try {
                Conf = new Config(filename, argCount, tabArg);
        } catch (Exceptions const &err) {
                throw (err);
        }
        Display();
        Exec();
}

Nanotekspice::~Nanotekspice()
{}

void Nanotekspice::Exec()
{
        std::string Input;

        while (Input != "exit" && std::cin.eof() != 1) {
                try {
                        signal(SIGINT, sigHandler);
                        std::cout << "> ";
                        std::getline(std::cin, Input);
                        if (Input == "display")
                                Display();
                        else if (Input == "simulate")
                                Simulate();
                        else if (Input == "loop")
                                Loop();
                        else if (Input == "dump")
                                Dump();
                        else
                                setValue(Input);
                }
                catch (Exceptions const &err) {
                        std::cout << err.what() << std::endl;
                }
        }
}

void Nanotekspice::Simulate()
{
        Conf->createLinks();
        for (unsigned int i = 0; i < Conf->getClocks().size(); i++) {
                Conf->getClocks()[i].reverseClock();
        }
}

void Nanotekspice::Loop()
{
        sigVal = true;
        signal(SIGINT, sigHandler);
        while (sigVal) {
                Simulate();
        }
}

void Nanotekspice::Dump()
{
        for (unsigned int i = 0; i < Conf->getInputs().size(); i++)
                Conf->getInputs()[i].dump();
        for (unsigned int o = 0; o < Conf->getOutputs().size(); o++)
                Conf->getOutputs()[o].dump();
        for (unsigned int t = 0; t < Conf->getTrues().size(); t++)
                Conf->getTrues()[t].dump();
        for (unsigned int f = 0; f < Conf->getFalses().size(); f++)
                Conf->getFalses()[f].dump();
        for (unsigned int c = 0; c < Conf->getClocks().size(); c++)
                Conf->getClocks()[c].dump();
        for (unsigned int c = 0; c < Conf->getChips().size(); c++)
                Conf->getChips()[c]->dump();
}

void sigHandler(int sig)
{
        (void)sig;
        Nanotekspice::sigVal = false;
}

void Nanotekspice::setValue(std::string inpVal)
{
        size_t pos = inpVal.find_last_of('=');
        std::string Inp;
        std::string Val;
        if (inpVal == "exit")
                return ;
        if (pos == std::string::npos)
                throw (CommandException("CommandException: "
					+ inpVal
					+ ": command not found"));
        Inp = inpVal.substr(0, pos);
        Val = inpVal.substr(pos + 1);
        for (unsigned int i = 0; i < Conf->getInputs().size(); i++) {
                if (Inp.compare(Conf->getInputs()[i].getName()) == 0) {
                        Conf->getInputs()[i].setValue(Val);
                        return ;
                }
        }
        throw (InputException("InputException: "
			      + Inp
			      + " is not defined or isn't an input"));
}

void Nanotekspice::Display()
{
        for (unsigned int i = 0; i < Conf->getOutputs().size(); i++) {
                std::cout << Conf->getOutputs()[i].getName() + "=";
		if (Conf->getOutputs()[i].getValue() == nts::Tristate::TRUE)
			std::cout << "1\n";
		if (Conf->getOutputs()[i].getValue() == nts::Tristate::FALSE)
			std::cout << "0\n";
        }
}

int Nanotekspice::getArgNb() const
{
        return argCount;
}

const char **Nanotekspice::getArgTab() const
{
        return tabArg;
}
