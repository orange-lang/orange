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
	std::vector<Type *> candidate_list;
	return matches(name, candidate_list);
}

bool Named::matches(std::string name, std::vector<Type *> candidates) const
{
	return m_name == name;
}