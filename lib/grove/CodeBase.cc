/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/CodeBase.h>

CodeLocation CodeBase::getLocation() const
{
	return m_location;
}

void CodeBase::setLocation(CodeLocation loc)
{
	m_location = loc;
}