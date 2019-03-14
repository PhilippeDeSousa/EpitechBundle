//
// EPITECH PROJECT, 2018
//
// File description:
//
//

#ifndef INPUT_HPP
# define INPUT_HPP

# include "IComponent.hpp"

namespace nts
{
	class Input : public IComponent
	{
	public:
		Input(std::string);
		~Input();
		std::string getName() const;
		virtual nts::Tristate compute(std:: size_t  pin = 1);
		virtual void setLink(std::size_t pin, nts::IComponent &other, std::
			size_t otherPin);
		virtual void dump() const;
		void setValue(std::string const &val);
		nts::Tristate &getValue();
	private:
		const std::string Name;
		nts::Tristate Value;
	};
}

#endif /* !INPUT_HPP */
