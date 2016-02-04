/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <libast/types/FutureType.h>
#include <libast/types/ReferenceType.h>

#include <libast/Typed.h>

#include <util/assertions.h>

Module* FutureType::getModule() const
{
	return Type::getModule();
}

std::string FutureType::getString() const
{
	return "future";
}

std::string FutureType::getSignature() const
{
	std::stringstream ss;
	ss << "Z" << this;
	return ss.str();
}

void FutureType::findDependencies()
{
	for (auto watcher : m_watchers)
	{
		addDependency(watcher->as<ASTNode *>());
	}
}

const Orange::Type* FutureType::copyType() const
{
	return FutureType::copy()->as<Type *>();
}


ASTNode* FutureType::copy() const
{
	throw fatal_error("FutureType should never be copied");
}

bool FutureType::isFutureTy() const
{
	return true;
}

FutureType::FutureType(Module* mod)
{
	assertExists(mod, "FutureType needs module");
	
	Type::m_module = mod;
}