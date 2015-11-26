/*
 ** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
 ** directory of this distribution.
 **
 ** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
 ** may not be copied, modified, or distributed except according to those terms.
 */

#include <grove/Named.h>

OString Named::getName() const
{
	return m_name;
}

OString Named::getMangledName() const
{
	return getName();
}

bool Named::matchesName(OString name) const
{
	return name == m_name;
}
