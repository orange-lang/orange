/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/Genericable.h>
#include <grove/Typed.h>
#include <grove/Named.h>

#include <grove/exceptions/fatal_error.h>

#include <grove/types/Type.h>

#include <util/assertions.h>

Genericable* Genericable::findInstance(const Type *type) const
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

bool Genericable::hasInstance(const Type *type) const
{
	return findInstance(type) != nullptr;
}