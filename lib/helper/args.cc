/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#include "helper/args.h"
#include <iostream>

void getArgs(int argc, char **argv, std::function<void(std::vector<std::string> arg, int loc)> cb) {
	for (int i = 1; i < argc; i++) {
		std::vector<std::string> a; 

		// Search until you find an argument that starts with - or -- 
		std::string arg = argv[i]; 
		if (arg.substr(0, 2) == "--") {
			// Begins with -- 
			a.push_back(arg.substr(0));
		} else if (arg[0] == '-') {
			// Begins with - 

			a.push_back(arg.substr(0, 2));

			if (arg.substr(2) != "")
				a.push_back(arg.substr(2));
		}

		if (a.size() != 0) {
			cb(a, i);
		}

		// TODO: windows machine arguments (/)
	}
}

const char* getParameter(std::vector<std::string> a, int argc, char **argv, int loc) {
	if (a.size() > 1) {
		return a[1].c_str();
	}

	int search = loc + 1;
	if (search >= argc) {
		return nullptr; 
	} 

	if (argv[search][0] == '-')
		return nullptr; 

	return argv[search];
}

bool cCommandOption::isSet() const { return m_set; }

cCommandOption::cCommandOption(std::vector<std::string> names, std::string description, bool arg) {
	this->names = names;
	this->description = description;
	this->hasArg = arg;
}

void cOptionsState::add(cCommandOption* option) { options.push_back(option); }
void cOptionsState::addState(cOptionsState* state) { states.push_back(state); }
std::vector<std::string> cOptionsState::unparsed() const { return m_unparsed; }

cOptionsState::cOptionsState(std::string name, std::string description) {
	this->name = name;
	this->description = description;
}

void cOptions::parse(int argc, char **argv) {
	// go through each argument in argv.
	// if it's an option, see if it matches any of the ones we've registered in this state 
	// if the option has an argument, get the next parameter. if it's another option, throw an error and quit. 
	// if the parameter matches a new state, switch to that state and continue.
	cOptionsState* curState = &mainState;
	curState->mActive = true;

	for (int i = 1; i < argc; i++) {
		std::string arg = argv[i];

		std::string param = "";
		std::string param_arg = "";

		if (arg.substr(0, 2) == "--") {
			// look in options for this full name 
			param = arg.substr(2);
		}	else if (arg[0] == '-') {
			param = arg.substr(1);
			if (param.length() > 1) {
				param = param.substr(0, 1);
				param_arg = arg.substr(2);
			}
		}	else {
			bool switchedState = false;
			for (cOptionsState* state : curState->states) {
				if (state->name == arg) {
					switchedState = true; 
					curState->mActive = false;
					curState = state;
					curState->mActive = true;
					break;
				}
			}

			if (switchedState == false) {
				curState->m_unparsed.push_back(arg);
			}

			continue;
		}

		if (param == "h" || param == "help") {
			std::string helpStr = "";
			if (curState->name != "") {
				helpStr = " for " + curState->name; 
			}

			std::cerr << name << std::endl << std::endl;
			std::cerr << "Available options" << helpStr << ":" << std::endl;

			for (cCommandOption* option : curState->options) {
				std::cerr << "\t";

				for (int i = 0; i < option->names.size(); i++) {
					if (option->names[i].length() == 1) {
						std::cerr << "-"; 
					} else std::cerr << "--";

					std::cerr << option->names[i];

					if (i + 1 < option->names.size()) std::cerr << " | ";
				}

				std::cerr << "\t\t" << option->description << std::endl; 
			}

			std::cerr << "\t-h | --help\t\tPrints this message\n";

			if (curState->states.size() > 0) {
				std::cerr << "\nAvailable commands" << helpStr << ":" << std::endl;
				for (cOptionsState* state : curState->states) {
					std::cerr << "\t" << state->name << "\t\t\t" << state->description << std::endl;
				}
			}

			exit(1);
		}

		// find param 
		for (cCommandOption* option : curState->options) {
			bool foundOption = false; 
			for (std::string name : option->names) {
				if (name == param) {
					foundOption = true; 
					break;
				}
			}

			if (foundOption) {
				option->m_set = true;

				if (option->hasArg == false && param_arg != "") {
					std::cerr << "error: unknown recognized argument " << param_arg << "for " << param << std::endl;
					exit(1);
				} else if (option->hasArg == true && param_arg != "") {
					option->arg_value = param_arg;
					break; 
				} else if (option->hasArg == true) {
					i++;

					if (i >= argc) {
						std::cerr << "fatal: no argument passed to parameter " << param << std::endl;
						exit(1);
					}

					param_arg = argv[i];

					if (param_arg[0] == '-') {
						std::cerr << "fatal: no argument passed to parameter " << param << std::endl; 
						exit(1);
					}

					option->arg_value = param_arg;
					break;
				}
			} 
		}
	}
}