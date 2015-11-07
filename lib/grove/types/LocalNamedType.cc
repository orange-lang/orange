/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <stdexcept>
#include <grove/Types/LocalNamedType.h>

Module* LocalNamedType::getModule() const
{
	return m_module;
}

LocalNamedType::LocalNamedType(Module* mod, std::string name, Type* ty)
: NamedType(name, ty)
{
	if (mod == nullptr)
	{
		throw std::invalid_argument("module must not be nullptr");
	}
	
	m_module = mod;
}