/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <iostream>
#include <sstream>
#include <cmd/ProgramOptions.h>
#include <cmd/OptionsState.h>
#include <cmd/StateFlag.h>

const int SHORT_ARG_LEN = 1;
const int LONG_ARG_LEN = 2;

bool isFlag(std::string arg)
{
	int first_alphanumeric = arg.find_first_not_of("-");

	return (first_alphanumeric == SHORT_ARG_LEN ||
			first_alphanumeric == LONG_ARG_LEN);
}

bool isHelpFlag(std::string flagName)
{
	return flagName == "h" || flagName == "help";
}

std::string ProgramOptions::getHelpString()
{
	std::stringstream ss;

	ss << getProgramName() << std::endl;
	ss << "\nActions:\n";

	for (auto state : getCurrentState()->getStates())
	{
		ss << "\t" << state->getStateName() << std::endl;
	}

	ss << "\nFlags:\n";

	for (auto flag : getCurrentState()->getFlags())
	{
		bool printDivider = (flag->hasShortName() && flag->hasLongName());

		ss << "\t";

		if (flag->hasShortName())
		{
			ss << "-" << flag->getShortName();
		}

		if (printDivider)
		{
			ss << " | ";
		}

		if (flag->hasLongName())
		{
			ss << "--" << flag->getLongName();
		}

		ss << "\n";
	}

	return ss.str();
}

std::string ProgramOptions::getProgramName() const
{
	return m_program_name;
}

OptionsState* ProgramOptions::getCurrentState() const
{
	return m_current_state;
}

OptionsState* ProgramOptions::getMainState() const
{
	return m_main_state;
}

int ProgramOptions::parse(int argc, char **argv)
{
	const std::string SHORT_ARG = "-";
	const std::string LONG_ARG = "--";

	m_current_state = getMainState();

	// Arguments to pass to m_current_state->run.
	std::vector<std::string> stateArguments;

	// Start at argc=1 to skip over program.
	for (int i = 1; i < argc; i++)
	{
		std::string curArg = (std::string)argv[i];

		if (isFlag(curArg))
		{
			// Find first non-"-" character
			auto first_alphanumeric = curArg.find_first_not_of("-");

			// Trigger is either - or --.
			std::string trigger = curArg.substr(0, first_alphanumeric);

			bool shortArg = (first_alphanumeric == SHORT_ARG.length());
			auto flagLen = shortArg ? 1 : curArg.length() - first_alphanumeric;
			std::string flagName = curArg.substr(first_alphanumeric, flagLen);

			std::string flagArg = "";

			if (shortArg && curArg.length() > 2)
			{
				flagArg = curArg.substr(2);
			}

			if (!shortArg && curArg.find("=") != curArg.npos)
			{
				flagArg = curArg.substr(curArg.find("=")+1);
				flagName = flagName.substr(0, curArg.find("=")-2);
			}

			StateFlag* flag = getCurrentState()->getFlag(flagName);

			if (flag == nullptr)
			{
				if (isHelpFlag(flagName))
				{
					std::cout << getHelpString() << std::endl;
					return 1;
				}
				else
				{
    				throw std::invalid_argument("Flag " + trigger + flagName +
    											" not recognized.");
				}
			}
			else
			{
				flag->setUsed(true);
			}


			if (flag->getNeedsValue())
			{
				if (flagArg != "")
				{
					flag->setValue(flagArg);
					continue;
				}

				// If the next argument is a flag, throw an error.
				if (isFlag(argv[i + 1]) == true)
				{
					throw std::invalid_argument("Flag " + curArg +
												"requires value.");
				}

				flag->setValue(argv[++i]);
			}
			else if (flagArg != "")
			{
				stateArguments.push_back(flagArg);
			}
		}
		else
		{
			// If the curArg is a state we can transition to, go there.
			// Otherwise, add curArg to stateArguments.
			OptionsState* transition = getCurrentState()->getState(curArg);
			if (transition != nullptr)
			{
				m_current_state = transition;
			}
			else
			{
				stateArguments.push_back(curArg);
			}
		}
	}

	OptionsState* runDelegate = getCurrentState()->getRunDelegate();
	if (runDelegate != nullptr)
	{
		return runDelegate->run(stateArguments);
	}
	else
	{
		return getCurrentState()->run(stateArguments);
	}
}

void ProgramOptions::addState(OptionsState *newState)
{
	getMainState()->addState(newState);
}

ProgramOptions::ProgramOptions(std::string programName)
{
	m_program_name = programName;
	m_main_state = new OptionsState("_main");
}
