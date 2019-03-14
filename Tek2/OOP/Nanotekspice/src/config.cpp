//
// EPITECH PROJECT, 2018
//
// File description:
//
//

#include "config.hpp"
#include <fstream>
#include <algorithm>

Config::Config(const std::string &filename, const int ac, const char **av)
        : Filename(filename), argCount(ac), argTab(av)
{
        try {
                size_t pos = filename.find_last_of('.');
                if (pos == std::string::npos ||
        	    filename.substr(pos, filename.length()) != ".nts")
                        throw (FileException
			       ("FileException: Wrong file format"));
                std::ifstream file;
                file.open(Filename, std::ifstream::in);
                if (!file)
                        throw (FileException("FileException: File"
					     + Filename + " doesn't exist"));
                else {
                        std::string s;
                        while (std::getline(file, s))
                                if (s[0] != '#' && s[0])
                                        File.push_back(s);
                        Config::setConf();
                }
        } catch (Exceptions const& err) {
                throw (err);
        }
}

Config::~Config()
{}

void Config::setConf()
{
        Config::setChipsets();
        Config::setInputs();
        Config::setOutputs();
        Config::setBools();
        Config::setClocks();
        Config::setLinks();
        Config::setChips();
        Config::createLinks();
}

std::vector<nts::IComponent *> &Config::getChips()
{
        return Chips;
}

std::vector<std::string> &Config::getChipNames()
{
        return ChipsNames;
}

void Config::setNames(std::string _chip, std::string _name)
{
        if (_chip == "4008" || _chip == "4081" || _chip == "4071" ||
        _chip == "4011" || _chip == "4001" || _chip == "4030" || _chip == "4069"
        || _chip == "4514" || _chip == "4040" || _chip == "4017" || _chip == "4094"
        || _chip == "4013")
                ChipsNames.push_back(_name);
}

void Config::setChips()
{
        for (unsigned int i = 0; i < Chipsets.size(); i++) {
		std::string _chp = Chipsets[i];
                if (_chp.find("4008") != std::string::npos)
                        Chips.push_back(new nts::Chip4008(_chp.substr(4)));
                else if (_chp.find("4081") != std::string::npos)
                        Chips.push_back(new nts::Chip4081(_chp.substr(4)));
                else if (_chp.find("4071") != std::string::npos)
                        Chips.push_back(new nts::Chip4071(_chp.substr(4)));
                else if (_chp.find("4011") != std::string::npos)
                        Chips.push_back(new nts::Chip4011(_chp.substr(4)));
                else if (_chp.find("4001") != std::string::npos)
                        Chips.push_back(new nts::Chip4001(_chp.substr(4)));
                else if (_chp.find("4030") != std::string::npos)
                        Chips.push_back(new nts::Chip4030(_chp.substr(4)));
                else if (_chp.find("4069") != std::string::npos)
                        Chips.push_back(new nts::Chip4069(_chp.substr(4)));
                else if (_chp.find("4514") != std::string::npos)
                        Chips.push_back(new nts::Chip4514(_chp.substr(4)));
                else if (_chp.find("4040") != std::string::npos)
                        Chips.push_back(new nts::Chip4040(_chp.substr(4)));
                else if (_chp.find("4017") != std::string::npos)
                        Chips.push_back(new nts::Chip4017(_chp.substr(4)));
                else if (_chp.find("4094") != std::string::npos)
                        Chips.push_back(new nts::Chip4094(_chp.substr(4)));
                else if (_chp.find("4013") != std::string::npos)
                        Chips.push_back(new nts::Chip4013(_chp.substr(4)));
                setNames(_chp.substr(0, 4), _chp.substr(4));
        }
}

void Config::setLinks()
{
        size_t post;
        size_t poss;
        for (unsigned int i = 0; i < File.size(); i++) {
                if (File[i].compare(".links:") == 0) {
                        for (unsigned int c = i + 1; c < File.size(); c++) {
                                post = File[c].find_last_of('\t');
                                if (post == File[c].npos)
                                        post = 0;
                                poss = File[c].find_last_of(' ');
                                if (poss == File[c].npos)
                                        poss = 0;
                                if (post < poss)
                                        Links.push_back(std::make_pair
							(File[c].substr
							 (0, poss + 1),
							 File[c].substr
							 (poss + 1)));
                                else
                                        Links.push_back(std::make_pair
							(File[c].substr
							 (0, post + 1),
							 File[c].substr
							 (post + 1)));
                        }
                }
        }
}

void Config::createLinks()
{
        size_t fpos;
        size_t spos;
        size_t fpin;
        size_t spin;
        for (unsigned int i = 0; i < Config::getLinks().size(); i ++) {
                fpos = Config::getLinks()[i].first.find_last_of(':');
                spos = Config::getLinks()[i].second.find_last_of(':');
                if (fpos == Config::getLinks()[i].first.npos ||
		    spos == Config::getLinks()[i].second.npos)
                        throw (SyntaxException("SyntaxException: "
					       + getLinks()[i].first
					       + getLinks()[i].second
					       + " syntax error"));
                fpin = std::stoi(getLinks()[i].first.substr(fpos + 1));
                spin = std::stoi(getLinks()[i].second.substr(spos + 1));
                getObj(getLinks()[i].first.substr(0, fpos))
			.setLink(fpin,
				 getObj(getLinks()[i].second.substr(0, spos))
				 , spin);
        }
}

nts::IComponent &Config::getObj(std::string Obj)
{
        for (unsigned int i = 0; i < Config::getInputs().size(); i++)
                if (Config::getInputs()[i].getName().compare(Obj) == 0) {
                        return (Config::getInputs()[i]);
        }
        for (unsigned int o = 0; o < Config::getOutputs().size(); o++) {
                if (Config::getOutputs()[o].getName().compare(Obj) == 0)
                        return (Config::getOutputs()[o]);
                }
        for (unsigned int t = 0; t < Config::getTrues().size(); t++) {
                if (Config::getTrues()[t].getName().compare(Obj) == 0)
                        return (Config::getTrues()[t]);
                }
        for (unsigned int f = 0; f < Config::getFalses().size(); f++) {
                if (Config::getFalses()[f].getName().compare(Obj) == 0)
                        return (Config::getFalses()[f]);
                }
        for (unsigned int c = 0; c < Config::getClocks().size(); c++) {
                if (Config::getClocks()[c].getName().compare(Obj) == 0)
                        return (Config::getClocks()[c]);
                }
        for (unsigned int c = 0; c < getChipNames().size(); c++) {
                if (getChipNames()[c].compare(Obj) == 0)
                        return *Chips[c];
        }
        throw (SyntaxException("SyntaxException: " + Obj + " doesn't exist"));
}

std::vector<std::pair<std::string, std::string> > &Config::getLinks()
{
        return Links;
}

void Config::setChipsets()
{
	for (unsigned int i = 0; i < File.size(); i++) {
		if (File[i].compare(".chipsets:") == 0 ||
		    File[i].compare(" .chipsets:") == 0) {
			for (unsigned int c = 0; File[c].compare(".links:")
				     != 0 && c < File.size(); c++) {
				File[c].erase(std::remove(File[c].begin(),
							  File[c].end(), '\t'),
					      File[c].end());
				File[c].erase(std::remove(File[c].begin(),
							  File[c].end(), ' '),
					      File[c].end());
				Chipsets.push_back(File[c]);
			}
		}
        }
        if (Chipsets.size() == 0)
                throw SyntaxException("SyntaxException: No chipsets");
}

std::vector<std::string> &Config::getChipsets()
{
        return Chipsets;
}

void Config::setInputs()
{
        std::vector<std::string> _inputs;

        try {
        	for (unsigned int i = 0; i < Chipsets.size(); i++)
        		if (Chipsets[i].find("input") != std::string::npos)
        			_inputs.push_back(Chipsets[i].substr(5));
                for (unsigned int i = 0; i < _inputs.size(); i++)
                        Inputs.push_back(nts::Input(_inputs[i]));
                for (unsigned int i = 0; i < getInputs().size(); i++) {
                        for (int ac = 2; ac < getArgCount(); ac++) {
                                std::string tmp (getArgTab()[ac]);
                                if (tmp.find(getInputs()[i].getName())
        			    != std::string::npos)
                                        getInputs()[i]
						.setValue(tmp.substr
							  (tmp.find_last_of
							   ('=') + 1));
                        }
                }
                for (unsigned int i = 0; i < getInputs().size(); i++)
                        if (getInputs()[i].getValue() ==
			    nts::Tristate::UNDEFINED)
                                throw InputException("InputException: "
						     + getInputs()[i].getName()
						     + " is not defined");
                } catch (InputException const& err) {
                        throw (err);
                }
}

std::vector<nts::Input> &Config::getInputs()
{
        return Inputs;
}

void Config::setOutputs()
{
        std::vector<std::string> _outputs;

	for (unsigned int i = 0; i < Chipsets.size(); i++) {
		if (Chipsets[i].find("output") != std::string::npos)
                        _outputs.push_back(Chipsets[i].substr(6));
        }
        std::sort (_outputs.begin(), _outputs.end());
        for (unsigned int c = 0; c < _outputs.size(); c++)
                Outputs.push_back(nts::Output(_outputs[c]));
}

std::vector<nts::Output> &Config::getOutputs()
{
        return Outputs;
}

void Config::setBools()
{
        std::vector<std::string> _true;
        std::vector<std::string> _false;

	for (unsigned int i = 0; i < Chipsets.size(); i++) {
		if (Chipsets[i].find("true") != std::string::npos)
			_true.push_back(Chipsets[i].substr(4));
        }
        for (unsigned int c = 0; c < _true.size(); c++)
                Trues.push_back(nts::True(_true[c]));
        for (unsigned int i = 0; i < Chipsets.size(); i++) {
		if (Chipsets[i].find("false") != std::string::npos)
			_false.push_back(Chipsets[i].substr(5));
        }
        for (unsigned int c = 0; c < _false.size(); c++)
                Falses.push_back(nts::False(_false[c]));
}

std::vector<nts::True> &Config::getTrues()
{
        return Trues;
}

std::vector<nts::False> &Config::getFalses()
{
        return Falses;
}

void Config::setClocks()
{
        std::vector<std::string> _clocks;

	for (unsigned int i = 0; i < Chipsets.size(); i++) {
		if (Chipsets[i].find("clock") != std::string::npos)
                        _clocks.push_back(Chipsets[i].substr(5));
        }
        for (unsigned int c = 0; c < _clocks.size(); c++)
                Clocks.push_back(nts::Clock(_clocks[c]));
        for (unsigned int i = 0; i < getClocks().size(); i++) {
                for (int ac = 2; ac < getArgCount(); ac++) {
                        std::string tmp (getArgTab()[ac]);
                        if (tmp.find(getClocks()[i].getName())
			    != std::string::npos)
                                getClocks()[i].
					setValue(tmp.substr
						 (tmp.find_last_of
						  ('=') + 1));
                }
        }
        for (unsigned int i = 0; i < getClocks().size(); i++) {
                if (getClocks()[i].getValue() == nts::Tristate::UNDEFINED)
                        throw InputException("InputException: "
					     + getClocks()[i].getName()
					     + " is not defined");
        }
}

std::vector<nts::Clock> &Config::getClocks()
{
        return Clocks;
}

int Config::getArgCount() const
{
        return argCount;
}

const char **Config::getArgTab() const
{
        return argTab;
}
