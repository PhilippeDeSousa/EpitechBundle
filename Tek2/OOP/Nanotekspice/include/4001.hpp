//
// EPITECH PROJECT, 2018
//
// File description:
//
//

#ifndef CHIP4001_HPP
# define CHIP4001_HPP

# include "IComponent.hpp"

namespace nts
{
	class Chip4001 : public IComponent
	{
	public:
		Chip4001(std::string);
		~Chip4001();
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

#endif /* !CHIP4001_HPP */
