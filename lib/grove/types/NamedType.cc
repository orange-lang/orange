/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <stdexcept>
#include <grove/types/NamedType.h>

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
		throw std::invalid_argument("name must not be empty");
	}

	if (type == nullptr)
	{
		throw std::invalid_argument("type must not be null");
	}

	m_name = name;
	m_type = type;
}
