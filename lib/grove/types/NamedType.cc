/*
** Copyright 2014-2017 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/types/NamedType.h>

#include <grove/exceptions/fatal_error.h>

Type* NamedType::getType() const
{
	return m_type;
}

std::string NamedType::getName() const
{
	return m_name;
}

NamedType::NamedType(std::string name, Type* type)
{
	if (name == "")
	{
		throw fatal_error("name was empty");
	}

	if (type == nullptr)
	{
		throw fatal_error("type was null");
	}

	m_name = name;
	m_type = type;
}
