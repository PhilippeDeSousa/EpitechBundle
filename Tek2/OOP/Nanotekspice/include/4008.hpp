//
// EPITECH PROJECT, 2018
//
// File description:
//
//

#ifndef CHIP4008_HPP
# define CHIP4008_HPP

# include "IComponent.hpp"

namespace nts
{
	class Chip4008 : public IComponent
	{
	public:
		Chip4008(std::string);
		~Chip4008();
		std::string getName() const;
		virtual nts::Tristate compute(std:: size_t  pin = 1);
		virtual void setLink(std::size_t pin, nts::IComponent &other, std::
			size_t otherPin);
		virtual void dump() const;
		std::vector<nts::Tristate> &getPin();
		nts::Tristate getSum(nts::Tristate, nts::Tristate, nts::Tristate);
		nts::Tristate getCarry(nts::Tristate, nts::Tristate, nts::Tristate);
		nts::Tristate getCout();
	private:
		const std::string Name;
		std::vector<nts::Tristate> chipPins;
		std::vector<nts::Tristate> Carry;
		nts::Tristate Value;
	};
}

#endif /* !CHIP4008_HPP */
