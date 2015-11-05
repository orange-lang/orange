/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <stdexcept>

#include <cmd/StateFlag.h>

bool StateFlag::hasShortName() const
{
	return m_shortform_name.length() != 0;
}

bool StateFlag::hasLongName() const
{
	return m_longform_name.length() != 0;
}

std::string StateFlag::getShortName() const
{
	return m_shortform_name;
}

std::string StateFlag::getLongName() const
{
	return m_longform_name;
}

std::string StateFlag::getValue() const
{
	return m_value;
}

bool StateFlag::getNeedsValue() const
{
	return m_needsValue;
}

bool StateFlag::getUsed() const
{
	return m_used;
}

void StateFlag::setUsed(bool used)
{
	m_used = used;
}

void StateFlag::setDescription(std::string description)
{
	m_description = description;
}

void StateFlag::setValue(std::string val)
{
	m_value = val;
}

StateFlag::StateFlag(std::string flagName, bool needsValue)
{
	if (flagName.length() == 0)
	{
		throw std::invalid_argument("flagName must not be empty.");
	}
	
	if (flagName.length() == 1)
	{
		m_shortform_name = flagName;
	}
	else
	{
		m_longform_name = flagName;
	}
	
	m_needsValue = needsValue;
}


StateFlag::StateFlag(std::string shortName, std::string longName, bool needsValue)
{
	if (shortName.length() != 1)
	{
		const char* error = "shortName must be exactly 1 character long.";
		throw std::invalid_argument(error);
	}

	if (longName.length() < 2)
	{
		const char* error = "longName must be longer than 1 character.";
		throw std::invalid_argument(error);
	}
	
	m_shortform_name = shortName;
	m_longform_name = longName;
	m_needsValue = needsValue;
}