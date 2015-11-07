/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/Namespace.h>

std::string Namespace::getName() const
{
	return m_name;
}

std::vector<Namespace *> Namespace::getChildren() const
{
	return m_children;
}

Namespace::Namespace(std::string name)
{
	if (name == "")
	{
		throw std::invalid_argument("name must not be empty.");
	}
	
	m_name = name;
}