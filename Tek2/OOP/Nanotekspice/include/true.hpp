//
// EPITECH PROJECT, 2018
//
// File description:
//
//

#ifndef TRUE_HPP
# define TRUE_HPP

# include "IComponent.hpp"

namespace nts
{
	class True : public IComponent
	{
	public:
		True(std::string);
		~True();
		std::string getName() const;
		virtual nts::Tristate compute(std:: size_t  pin = 1);
		virtual void setLink(std::size_t pin, nts::IComponent &other, std::
			size_t otherPin);
		virtual void dump() const;
		nts::Tristate getValue() const;
	private:
		const std::string Name;
		nts::Tristate Value;
	};
}

# endif /* !TRUE_HPP */
