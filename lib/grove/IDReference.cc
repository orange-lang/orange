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

llvm::Value* IDReference::getPointer() const
{
	return findNode()->getPointer();
}

bool IDReference::hasPointer() const
{
	return findNode()->hasPointer();
}

Valued* IDReference::findNode() const
{
	return findNamed(getName())->as<Valued *>();
}

std::string IDReference::getName() const
{
	return m_name;
}

void IDReference::resolve()
{
	auto typed = findNamed(getName())->as<Typed *>();

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
