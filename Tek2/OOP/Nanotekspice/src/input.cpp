//
// EPITECH PROJECT, 2018
//
// File description:
//
//

#include "input.hpp"

nts::Input::Input(std::string name)
        : Name(name), Value(nts::Tristate::UNDEFINED)
{
}

void nts::Input::dump() const
{
        std::cout << getName() + ": Input, value = ";
        std::cout << Value;
        std::cout << "\n\n";
}

nts::Tristate &nts::Input::getValue()
{
        return Value;
}

void nts::Input::setValue(std::string const &val)
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

nts::Tristate nts::Input::compute(std::size_t pin)
{
        if (pin != 1)
                throw (PinException("PinException: pin "
				    + std::to_string(pin)
				    + " doesn't exist"));
        return Value;
}

void nts::Input::setLink(std::size_t pin, nts::IComponent &other, std::
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

std::string nts::Input::getName() const
{
        return Name;
}

nts::Input::~Input()
{}
