/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/IDReference.h>
#include <grove/Valued.h>
#include <grove/Named.h>
#include <grove/Typed.h>

#include <util/assertions.h>

Valued* IDReference::findNode() const
{
	auto valued = dynamic_cast<Valued *>(findNamed(getName()));
	assertExists(valued, "Could not find named node.");
	
	return valued;
}

std::string IDReference::getName() const
{
	return m_name;
}

void IDReference::resolve()
{
	auto typed = dynamic_cast<Typed *>(findNamed(getName()));
	assertExists(typed, "Could not find named node.");
	
	auto ty = typed->getType();
	assertExists(ty, "Could not assign type.");
	
	setType(ty);
}

void IDReference::build()
{
	setValue(findNode()->getValue());
	assertExists(getValue(), "Value was not assigned.");
}

IDReference::IDReference(std::string name)
{
	if (name == "")
	{
		throw std::invalid_argument("name cannot be null.");
	}
	
	m_name = name;
}