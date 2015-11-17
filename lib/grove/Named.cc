/*
 ** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
 ** directory of this distribution.
 **
 ** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
 ** may not be copied, modified, or distributed except according to those terms.
 */

#include <grove/Named.h>

std::string Named::getName() const
{
	return m_name;
}

bool Named::matches(std::string name) const
{
	return matches(name, nullptr);
}

bool Named::matches(std::string name, Type* type) const
{
	return m_name == name;
}