//
// EPITECH PROJECT, 2018
//
// File description:
//
//

#ifndef CONFIG_HPP
# define CONFIG_HPP

# include "errors.hpp"
# include "input.hpp"
# include "output.hpp"
# include "true.hpp"
# include "false.hpp"
# include "clock.hpp"
# include "4008.hpp"
# include "4081.hpp"
# include "4071.hpp"
# include "4011.hpp"
# include "4001.hpp"
# include "4030.hpp"
# include "4069.hpp"
# include "4514.hpp"
# include "4040.hpp"
# include "4017.hpp"
# include "4094.hpp"
# include "4013.hpp"

class Config
{
public:
        Config(const std::string &, const int, const char **);
        ~Config();
        void setInputs();
        void setOutputs();
        void setBools();
        void setClocks();
        void setLinks();
        void setChipsets();
        void createLinks();
        void setChips();
        void setConf();
        nts::IComponent &getObj(std::string Obj);
        std::vector<nts::Input> &getInputs();
        std::vector<nts::Output> &getOutputs();
        std::vector<std::string> &getChipsets();
        std::vector<nts::True> &getTrues();
        std::vector<nts::False> &getFalses();
        std::vector<nts::Clock> &getClocks();
        std::vector<std::string> &getChipNames();
        void setNames(std::string, std::string);
        std::vector<std::pair<std::string, std::string> > &getLinks();
        const char **getArgTab() const;
        int getArgCount() const;
        std::vector<nts::IComponent *> &getChips();
private:
        const std::string &Filename;
        std::vector<nts::Input> Inputs;
        std::vector<nts::Output> Outputs;
        std::vector<nts::False> Falses;
        std::vector<nts::True> Trues;
        std::vector<nts::Clock> Clocks;
        std::vector<std::string> File;
        std::vector<std::string> Chipsets;
        std::vector<std::pair<std::string, std::string> > Links;
        std::vector<nts::IComponent *> Chips;
        std::vector<std::string> ChipsNames;
        std::string chipName;
        const int argCount;
        const char **argTab;

};

#endif /* !CONFIG_HPP */
