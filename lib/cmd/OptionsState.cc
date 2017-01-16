/*
** Copyright 2014-2017 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <stdexcept>

#include <cmd/OptionsState.h>
#include <cmd/StateFlag.h>

std::string OptionsState::getStateName() const
{
	return m_state_name;
}

OptionsState* OptionsState::getState(std::string stateName) const
{
	for (auto state : m_states)
	{
		if (state->getStateName() == stateName)
		{
			return state;
		}
	}
	
	return nullptr;
}

std::vector<OptionsState *> OptionsState::getStates() const
{
	return m_states;
}

std::vector<StateFlag *> OptionsState::getFlags() const
{
	return m_flags;
}

StateFlag* OptionsState::getFlag(std::string name) const
{
	// No flag with a blank name will ever exist.
	if (name.length() == 0)
	{
		return nullptr;
	}
	
	bool compareShortNames = (name.length() == 1);
	
	for (auto flag : m_flags)
	{
		if ((compareShortNames && flag->getShortName() == name) ||
			(!compareShortNames && flag->getLongName() == name))
		{
			return flag;
		}
	}
	
	return nullptr;
}

OptionsState* OptionsState::getRunDelegate() const
{
	return m_run_delegate;
}

void OptionsState::addState(OptionsState *newState)
{
	if (newState == nullptr)
	{
		throw std::invalid_argument("newState must not be nullptr");
	}
	
	m_states.push_back(newState);
}

void OptionsState::addFlag(StateFlag *newFlag)
{
	if (newFlag == nullptr)
	{
		throw std::invalid_argument("newFlag must not be nullptr");
	}
	
	m_flags.push_back(newFlag);
}

void OptionsState::setRunDelegate(OptionsState *runDelegate)
{
	m_run_delegate = runDelegate;
}

int OptionsState::run(std::vector<std::string> args)
{
	// Do nothing, override for custom logic.
	return 0;
}

OptionsState::OptionsState(std::string stateName)
{
	if (stateName.length() == 0)
	{
		throw std::invalid_argument("stateName cannot be empty.");
	}
	
	m_state_name = stateName;
}

OptionsState::~OptionsState()
{
	// Do nothing.
}