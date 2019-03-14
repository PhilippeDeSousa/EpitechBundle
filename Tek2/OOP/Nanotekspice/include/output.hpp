//
// EPITECH PROJECT, 2018
//
// File description:
//
//

#ifndef OUTPUT_HPP
# define OUTPUT_HPP

#include "IComponent.hpp"

namespace nts
{
	class Output : public IComponent
	{
	public:
		Output(std::string);
		~Output();
		std::string getName() const;
		nts::Tristate getValue();
		virtual nts::Tristate compute(std:: size_t  pin = 1);
		virtual void setLink(std::size_t pin, nts::IComponent &other, std::
			size_t otherPin);
		virtual void dump() const;
	private:
		const std::string Name;
		nts::Tristate Value;
		bool Link;
	};
}

#endif /* !OUTPUT_HPP */
