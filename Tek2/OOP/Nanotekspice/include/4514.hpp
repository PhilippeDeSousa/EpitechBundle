//
// EPITECH PROJECT, 2018
//
// File description:
//
//

#ifndef CHIP4514_HPP
# define CHIP4514_HPP

# include "IComponent.hpp"

namespace nts
{
	class Chip4514 : public IComponent
	{
	public:
		Chip4514(std::string);
		~Chip4514();
		std::string getName() const;
		virtual nts::Tristate compute(std:: size_t  pin = 1);
		virtual void setLink(std::size_t pin, nts::IComponent &other, std::
			size_t otherPin);
		virtual void dump() const;
		std::vector<nts::Tristate> &getPin();
		void getInputA();
		void getInputB();
		void getInputC();
		void getInputD();
		void getInhibit();
	private:
		const std::string Name;
		std::vector<nts::Tristate> chipPins;
	};
}

#endif /* !CHIP4514_HPP */
