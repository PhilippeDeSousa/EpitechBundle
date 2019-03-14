//
// EPITECH PROJECT, 2018
//
// File description:
//
//

#include "clock.hpp"

nts::Clock::Clock(std::string name)
        : Name(name), Value(nts::Tristate::UNDEFINED)
{
}

nts::Tristate nts::Clock::getValue() const
{
        return Value;
}

void nts::Clock::dump() const
{
        std::cout << getName() + ": Clock, value = ";
        std::cout << Value;
        std::cout << "\n\n";
}

void nts::Clock::setValue(std::string const &val)
{
        if (val == "0")
                Value = nts::Tristate::FALSE;
        else if (val == "1")
                Value = nts::Tristate::TRUE;
        else
                throw (InputException("InputException: "
				      + getName()
				      + ": value must be 0 or 1"));
}

void nts::Clock::reverseClock()
{
        if (Value == nts::Tristate::TRUE)
                Value = nts::Tristate::FALSE;
        else if (Value == nts::Tristate::FALSE)
                Value = nts::Tristate::TRUE;
}

void nts::Clock::setLink(std::size_t pin, nts::IComponent &other, std::
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

nts::Tristate nts::Clock::compute(std::size_t pin)
{
        if (pin != 1)
                throw (PinException("PinException: pin "
				    + std::to_string(pin)
				    + " doesn't exist"));
        return (Value);
}

std::string nts::Clock::getName() const
{
        return Name;
}

nts::Clock::~Clock()
{}
