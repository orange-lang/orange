/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/Staticable.h>

void Staticable::setStatic(bool isStatic)
{
	m_static = isStatic;
}

const bool Staticable::getStatic() const
{
	return m_static;
}