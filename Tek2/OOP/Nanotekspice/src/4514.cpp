//
// EPITECH PROJECT, 2018
//
// File description:
//
//

#include "4514.hpp"

nts::Chip4514::Chip4514(std::string name)
        : Name(name)
{
        for (int i = 0; i < 25; i++) {
                chipPins.push_back(nts::Tristate::TRUE);
        }
        chipPins[12] = nts::Tristate::UNDEFINED;
        chipPins[24] = nts::Tristate::UNDEFINED;
}

void nts::Chip4514::dump() const
{
        std::cout << Name + ": Chip 4514\n";
        for (int i = 1; i < 25; i++) {
                std::cout << "\tPin n°";
                std::cout << i;
                std::cout << ", value: ";
                if (chipPins[i] == nts::Tristate::UNDEFINED)
                        std::cout << "Ignored" << std::endl;
                else
                        std::cout << chipPins[i] << std::endl;;
        }
}

std::vector<nts::Tristate> &nts::Chip4514::getPin()
{
        return chipPins;
}

void nts::Chip4514::getInputA()
{
        if (chipPins[2] != nts::Tristate::TRUE) {
                chipPins[4] = nts::Tristate::FALSE;
                chipPins[6] = nts::Tristate::FALSE;
                chipPins[8] = nts::Tristate::FALSE;
                chipPins[9] = nts::Tristate::FALSE;
                chipPins[13] = nts::Tristate::FALSE;
                chipPins[15] = nts::Tristate::FALSE;
                chipPins[17] = nts::Tristate::FALSE;
                chipPins[19] = nts::Tristate::FALSE;
        }
        else {
                chipPins[5] = nts::Tristate::FALSE;
                chipPins[7] = nts::Tristate::FALSE;
                chipPins[10] = nts::Tristate::FALSE;
                chipPins[11] = nts::Tristate::FALSE;
                chipPins[12] = nts::Tristate::FALSE;
                chipPins[14] = nts::Tristate::FALSE;
                chipPins[16] = nts::Tristate::FALSE;
                chipPins[18] = nts::Tristate::FALSE;
                chipPins[20] = nts::Tristate::FALSE;
        }
}

void nts::Chip4514::getInputB()
{
        if (chipPins[3] != nts::Tristate::TRUE) {
                chipPins[4] = nts::Tristate::FALSE;
                chipPins[5] = nts::Tristate::FALSE;
                chipPins[8] = nts::Tristate::FALSE;
                chipPins[10] = nts::Tristate::FALSE;
                chipPins[15] = nts::Tristate::FALSE;
                chipPins[16] = nts::Tristate::FALSE;
                chipPins[19] = nts::Tristate::FALSE;
                chipPins[20] = nts::Tristate::FALSE;
        }
        else {
                chipPins[6] = nts::Tristate::FALSE;
                chipPins[7] = nts::Tristate::FALSE;
                chipPins[9] = nts::Tristate::FALSE;
                chipPins[11] = nts::Tristate::FALSE;
                chipPins[12] = nts::Tristate::FALSE;
                chipPins[13] = nts::Tristate::FALSE;
                chipPins[14] = nts::Tristate::FALSE;
                chipPins[17] = nts::Tristate::FALSE;
                chipPins[18] = nts::Tristate::FALSE;
        }
}

void nts::Chip4514::getInputC()
{
        if (chipPins[21] != nts::Tristate::TRUE) {
                chipPins[4] = nts::Tristate::FALSE;
                chipPins[5] = nts::Tristate::FALSE;
                chipPins[6] = nts::Tristate::FALSE;
                chipPins[7] = nts::Tristate::FALSE;
                chipPins[13] = nts::Tristate::FALSE;
                chipPins[14] = nts::Tristate::FALSE;
                chipPins[15] = nts::Tristate::FALSE;
                chipPins[16] = nts::Tristate::FALSE;
        }
        else {
                chipPins[8] = nts::Tristate::FALSE;
                chipPins[9] = nts::Tristate::FALSE;
                chipPins[10] = nts::Tristate::FALSE;
                chipPins[11] = nts::Tristate::FALSE;
                chipPins[12] = nts::Tristate::FALSE;
                chipPins[17] = nts::Tristate::FALSE;
                chipPins[18] = nts::Tristate::FALSE;
                chipPins[19] = nts::Tristate::FALSE;
                chipPins[20] = nts::Tristate::FALSE;
        }
}

void nts::Chip4514::getInputD()
{
        if (chipPins[22] != nts::Tristate::TRUE) {
                chipPins[13] = nts::Tristate::FALSE;
                chipPins[14] = nts::Tristate::FALSE;
                chipPins[15] = nts::Tristate::FALSE;
                chipPins[16] = nts::Tristate::FALSE;
                chipPins[17] = nts::Tristate::FALSE;
                chipPins[18] = nts::Tristate::FALSE;
                chipPins[19] = nts::Tristate::FALSE;
                chipPins[20] = nts::Tristate::FALSE;
        }
        else {
                chipPins[4] = nts::Tristate::FALSE;
                chipPins[5] = nts::Tristate::FALSE;
                chipPins[6] = nts::Tristate::FALSE;
                chipPins[7] = nts::Tristate::FALSE;
                chipPins[8] = nts::Tristate::FALSE;
                chipPins[9] = nts::Tristate::FALSE;
                chipPins[10] = nts::Tristate::FALSE;
                chipPins[11] = nts::Tristate::FALSE;
                chipPins[12] = nts::Tristate::FALSE;
        }
}

void nts::Chip4514::getInhibit()
{
        if (chipPins[23] == nts::Tristate::TRUE) {
                for (int i = 0; i < 25; i++) {
                        chipPins[i] = nts::Tristate::TRUE;
                }
                chipPins[12] = nts::Tristate::UNDEFINED;
                chipPins[24] = nts::Tristate::UNDEFINED;
        }
}

nts::Tristate nts::Chip4514::compute(std::size_t pin)
{
        if (pin < 1)
                throw (PinException("PinException: pin "
				    + std::to_string(pin)
				    + " doesn't exist"));
        if (chipPins[1] != nts::Tristate::FALSE) {
                getInputA();
                getInputB();
                getInputC();
                getInputD();
        }
        getInhibit();
        return chipPins[pin];
}

void nts::Chip4514::setLink(std::size_t pin, nts::IComponent &other, std::
        size_t otherPin)
{
        if (pin < 1 || pin > 23)
                throw (PinException("PinException: pin "
				    + std::to_string(pin)
				    + " doesn't exist"));
        else if (otherPin < 1)
                throw (PinException("PinException: pin "
				    + std::to_string(otherPin)
				    + " doesn't exist"));
        chipPins[pin] = other.compute(otherPin);
}

std::string nts::Chip4514::getName() const
{
        return Name;
}

nts::Chip4514::~Chip4514()
{}
