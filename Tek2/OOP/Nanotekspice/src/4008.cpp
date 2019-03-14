//
// EPITECH PROJECT, 2018
//
// File description:
//
//

#include "4008.hpp"

nts::Chip4008::Chip4008(std::string name)
        : Name(name)
{
        for (int i = 0; i < 16; i++) {
                chipPins.push_back(nts::Tristate::UNDEFINED);
        }
        chipPins[8] = nts::Tristate::UNDEFINED;
        chipPins[16] = nts::Tristate::UNDEFINED;
        for (int i = 0; i < 5; i++) {
                Carry.push_back(nts::Tristate::UNDEFINED);
        }
}

std::vector<nts::Tristate> &nts::Chip4008::getPin()
{
        return chipPins;
}

void nts::Chip4008::dump() const
{
        std::cout << Name + ": Chip 4008\n";
        for (int i = 0; i < 17; i++) {
                std::cout << "\tPin n°";
                std::cout << i;
                std::cout << ", value: ";
                if (chipPins[i] == nts::Tristate::UNDEFINED)
                        std::cout << "Ignored" << std::endl;
                else
                        std::cout << chipPins[i] << std::endl;;
        }
}

nts::Tristate nts::Chip4008::compute(std::size_t pin)
{
        if (pin < 1)
                throw (PinException("PinException: pin "
				    + std::to_string(pin)
				    + " doesn't exist"));
        chipPins[10] = getSum(chipPins[6], chipPins[7], chipPins[9]);
        Carry[2] = getCarry(chipPins[6], chipPins[7], chipPins[9]);
        chipPins[11] = getSum(chipPins[4], chipPins[5], Carry[2]);
        Carry[3] = getCarry(chipPins[4], chipPins[5], Carry[2]);
        chipPins[12] = getSum(chipPins[2], chipPins[3], Carry[3]);
        Carry[4] = getCarry(chipPins[2], chipPins[3], Carry[3]);
        chipPins[13] = getSum(chipPins[15], chipPins[1], Carry[4]);
        chipPins[14] = getCout();

        return chipPins[pin];
}

nts::Tristate nts::Chip4008::getCout()
{
        int a = 0;

        for (int i = 0; i < 5; i++) {
                if (Carry[i] == nts::Tristate::TRUE)
                        a += 1;
        }
        if (a >= 2)
                return nts::Tristate::TRUE;
        return nts::Tristate::FALSE;
}

nts::Tristate nts::Chip4008::getSum(nts::Tristate ft,
				    nts::Tristate sd,
				    nts::Tristate td)
{
        if (ft == nts::Tristate::TRUE && sd != nts::Tristate::TRUE
	    && td != nts::Tristate::TRUE)
                return nts::Tristate::TRUE;
        else if (ft != nts::Tristate::TRUE && sd == nts::Tristate::TRUE
		 && td != nts::Tristate::TRUE)
                return nts::Tristate::TRUE;
        else if (ft != nts::Tristate::TRUE && sd != nts::Tristate::TRUE
		 && td == nts::Tristate::TRUE)
                return nts::Tristate::TRUE;
        else if (ft == nts::Tristate::TRUE && sd == nts::Tristate::TRUE
		 && td == nts::Tristate::TRUE)
                return nts::Tristate::TRUE;

        return nts::Tristate::FALSE;
}

nts::Tristate nts::Chip4008::getCarry(nts::Tristate ft,
				      nts::Tristate sd,
				      nts::Tristate td)
{
        if (ft == nts::Tristate::TRUE && sd == nts::Tristate::TRUE
	    && td != nts::Tristate::TRUE)
                return nts::Tristate::TRUE;
        else if (ft != nts::Tristate::TRUE && sd == nts::Tristate::TRUE
		 && td == nts::Tristate::TRUE)
                return nts::Tristate::TRUE;
        else if (ft == nts::Tristate::TRUE && sd != nts::Tristate::TRUE
		 && td == nts::Tristate::TRUE)
                return nts::Tristate::TRUE;
        else if (ft == nts::Tristate::TRUE && sd == nts::Tristate::TRUE
		 && td == nts::Tristate::TRUE)
                return nts::Tristate::TRUE;

        return nts::Tristate::FALSE;
}

void nts::Chip4008::setLink(std::size_t pin, nts::IComponent &other, std::
        size_t otherPin)
{
        if (pin < 1 || pin > 16)
                throw (PinException("PinException: pin "
				    + std::to_string(pin)
				    + " doesn't exist"));
        else if (otherPin < 1)
                throw (PinException("PinException: pin "
				    + std::to_string(otherPin)
				    + " doesn't exist"));
        chipPins[pin] = other.compute(otherPin);
}

std::string nts::Chip4008::getName() const
{
        return Name;
}

nts::Chip4008::~Chip4008()
{}
