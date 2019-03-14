//
// EPITECH PROJECT, 2018
//
// File description:
//
//

#include "false.hpp"

nts::False::False(std::string name)
        : Name(name), Value(nts::Tristate::FALSE)
{
}

void nts::False::dump() const
{
        std::cout << getName() + ": False input, value = ";
        std::cout << Value;
        std::cout << "\n\n";
}

nts::Tristate nts::False::getValue() const
{
        return Value;
}

std::string nts::False::getName() const
{
        return Name;
}

nts::Tristate nts::False::compute(std::size_t pin)
{
        if (pin != 1)
                throw (PinException("PinException: pin "
				    + std::to_string(pin)
				    + " doesn't exist"));
        return (Value);
}

void nts::False::setLink(std::size_t pin, nts::IComponent &other, std::
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

nts::False::~False()
{}
