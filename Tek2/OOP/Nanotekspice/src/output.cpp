//
// EPITECH PROJECT, 2018
//
// File description:
//
//

#include "output.hpp"

nts::Output::Output(std::string name)
        : Name(name), Value(nts::Tristate::UNDEFINED), Link(FALSE)
{
}

void nts::Output::dump() const
{
        std::cout << getName() + ": Output, value = ";
        std::cout << Value;
        std::cout << "\n\n";
}

std::string nts::Output::getName() const
{
        return Name;
}

nts::Tristate nts::Output::compute(std::size_t pin)
{
        if (pin != 1)
                throw (PinException("PinException: pin "
				    + std::to_string(pin)
				    + " doesn't exist"));
        return Value;
}

void nts::Output::setLink(std::size_t pin, nts::IComponent &other, std::
        size_t otherPin)
{
        if (pin != 1)
                throw (PinException("PinException: pin "
				    + std::to_string(pin)
				    + " doesn't exist"));
        Value = other.compute(otherPin);
}

nts::Tristate nts::Output::getValue()
{
        return Value;
}

nts::Output::~Output()
{}
