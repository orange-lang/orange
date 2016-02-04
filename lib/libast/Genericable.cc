/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <libast/Genericable.h>
#include <libast/Typed.h>
#include <libast/Named.h>

#include <libast/exceptions/fatal_error.h>

#include <libast/types/Type.h>

#include <util/assertions.h>

Genericable* Genericable::findInstance(const Orange::Type* type) const
{
	if (isGeneric() == false)
	{
		throw fatal_error("cannot find instance of non-generic");
	}
	
	for (auto instance : m_instances)
	{
		auto ty = instance->getType();
		assertExists(ty, "Instance did not have a type!");
		
		if (ty == type || instance->matchesType(type))
		{
			return instance;
		}
	}
	
	return nullptr;
}

Genericable* Genericable::getInstanceParent() const
{
	return m_instance_of;
}

bool Genericable::isInstance() const
{
	return m_instance_of != nullptr;
}

bool Genericable::hasInstance(const Orange::Type* type) const
{
	return findInstance(type) != nullptr;
}