//
// EPITECH PROJECT, 2018
//
// File description:
//
//

#include "4069.hpp"

nts::Chip4069::Chip4069(std::string name)
        : Name(name)
{
        for (int i = 0; i < 15; i++) {
                chipPins.push_back(nts::Tristate::UNDEFINED);
        }
}

void nts::Chip4069::dump() const
{
        std::cout << Name + ": Chip 4069\n";
        for (int i = 1; i < 15; i++) {
                std::cout << "\tPin n°";
                std::cout << i;
                std::cout << ", value: ";
                if (chipPins[i] == nts::Tristate::UNDEFINED)
                        std::cout << "Ignored" << std::endl;
                else
                        std::cout << chipPins[i] << std::endl;;
        }
}

std::vector<nts::Tristate> &nts::Chip4069::getPin()
{
        return chipPins;
}

nts::Tristate nts::Chip4069::getValue(nts::Tristate pin)
{
        if (pin == nts::Tristate::TRUE)
                return nts::Tristate::FALSE;
        return nts::Tristate::TRUE;
}

nts::Tristate nts::Chip4069::compute(std::size_t pin)
{
        if (pin < 1)
                throw (PinException("PinException: pin "
				    + std::to_string(pin)
				    + " doesn't exist"));
        chipPins[2] = getValue(chipPins[1]);
        chipPins[4] = getValue(chipPins[3]);
        chipPins[6] = getValue(chipPins[5]);
        chipPins[8] = getValue(chipPins[9]);
        chipPins[10] = getValue(chipPins[11]);
        chipPins[12] = getValue(chipPins[13]);
        return chipPins[pin];
}

void nts::Chip4069::setLink(std::size_t pin, nts::IComponent &other, std::
        size_t otherPin)
{
        if (pin < 1 || pin > 14)
                throw (PinException("PinException: pin "
				    + std::to_string(pin)
				    + " doesn't exist"));
        else if (otherPin < 1)
                throw (PinException("PinException: pin "
				    + std::to_string(otherPin)
				    + " doesn't exist"));
        if (other.compute(otherPin) == nts::Tristate::UNDEFINED)
                other.setLink(otherPin, *this, pin);
        chipPins[pin] = other.compute(otherPin);
}

std::string nts::Chip4069::getName() const
{
        return Name;
}

nts::Chip4069::~Chip4069()
{}
