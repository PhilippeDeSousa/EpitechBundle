//
// EPITECH PROJECT, 2018
//
// File description:
//
//

#ifndef CLOCK_HPP
# define CLOCK_HPP

# include "IComponent.hpp"

namespace nts
{
	class Clock : public IComponent
	{
	public:
		Clock(std::string);
		~Clock();
		std::string getName() const;
		virtual nts::Tristate compute(std:: size_t  pin = 1);
		virtual void setLink(std::size_t pin, nts::IComponent &other, std::
			size_t otherPin);
		virtual void dump() const;
		void setValue(std::string const &val);
		nts::Tristate getValue() const;
		void reverseClock();
	private:
		const std::string Name;
		nts::Tristate Value;
	};
}

# endif /* !CLOCK_HPP */
