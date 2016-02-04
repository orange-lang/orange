/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <libast/types/LocalNamedType.h>

#include <libast/exceptions/fatal_error.h>



Module* LocalNamedType::getModule() const
{
	return m_module;
}

LocalNamedType::LocalNamedType(Module* mod, std::string name, Orange::Type* ty)
: NamedType(name, ty)
{
	if (mod == nullptr)
	{
		throw fatal_error("module was null");
	}
	
	m_module = mod;
}