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
		throw std::runtime_error("cannot create instance of non-generic");
	}
	
	return nullptr;
}

Genericable* Genericable::findInstance(Type *type) const
{
	if (isGeneric() == false)
	{
		throw std::runtime_error("cannot find instance of non-generic");
	}
	
	for (auto instance : m_instances)
	{
		auto ty = instance->getType();
		assertExists(ty, "Instance did not have a type!");
		
		if (instance->is<Named *>())
		{
			auto named = instance->as<Named *>();
			
			if (named->matches(named->getName(), type))
			{
				return instance;
			}
		}
		else if (ty == type)
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