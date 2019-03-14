//
// EPITECH PROJECT, 2018
//
// File description:
//
//

#ifndef CHIP4011_HPP
# define CHIP4011_HPP

# include "IComponent.hpp"

namespace nts
{
	class Chip4011 : public IComponent
	{
	public:
		Chip4011(std::string);
		~Chip4011();
		std::string getName() const;
		virtual nts::Tristate compute(std:: size_t  pin = 1);
		virtual void setLink(std::size_t pin, nts::IComponent &other, std::
			size_t otherPin);
		virtual void dump() const;
		std::vector<nts::Tristate> &getPin();
		nts::Tristate getValue(nts::Tristate, nts::Tristate);
	private:
		const std::string Name;
		std::vector<nts::Tristate> chipPins;
	};
}

#endif /* !CHIP4011_HPP */
