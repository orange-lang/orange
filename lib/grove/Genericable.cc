/*
** Copyright 2014-2017 Robert Fratto. See the LICENSE.txt file at the top-level
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

bool Genericable::isGeneric() const
{
	return false;
}

Genericable* Genericable::createInstance(Type *type)
{
	if (isGeneric() == false)
	{
		throw fatal_error("cannot create instance of non-generic");
	}
	
	return nullptr;
}

Genericable* Genericable::findInstance(Type *type) const
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

bool Genericable::hasInstance(Type *type) const
{
	return findInstance(type) != nullptr;
}