//
// EPITECH PROJECT, 2018
//
// File description:
//
//

#ifndef FALSE_HPP
# define FALSE_HPP

# include "IComponent.hpp"

namespace nts
{
	class False : public IComponent
	{
	public:
		False(std::string);
		~False();
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

# endif /* !FALSE_HPP */
