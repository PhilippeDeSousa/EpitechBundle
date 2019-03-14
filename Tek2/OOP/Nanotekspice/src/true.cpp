//
// EPITECH PROJECT, 2018
//
// File description:
//
//

#include "true.hpp"

nts::True::True(std::string name)
        : Name(name), Value(nts::Tristate::TRUE)
{}

void nts::True::dump() const
{
        std::cout << getName() + ": True input, value = ";
        std::cout << Value;
        std::cout << "\n\n";
}

nts::Tristate nts::True::getValue() const
{
        return Value;
}

std::string nts::True::getName() const
{
        return Name;
}

void nts::True::setLink(std::size_t pin, nts::IComponent &other, std::
        size_t otherPin)
{
        if (pin != 1)
                throw (PinException("PinException: pin "
				    + std::to_string(pin)
				    + " doesn't exist"));
        else if (otherPin < 1)
                throw (PinException("PinException: pin "
				    + std::to_string(otherPin)
				    + " doesn't exist"));
        other.setLink(otherPin, *this, pin);
}

nts::Tristate nts::True::compute(std::size_t pin)
{
        if (pin != 1)
                throw (PinException("PinException: pin "
				    + std::to_string(pin)
				    + " doesn't exist"));
        return Value;
}

nts::True::~True()
{}
