/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/Protectable.h>

void Protectable::setProtectionLevel(ProtectionLevel &level)
{
	m_level = level;
}

const ProtectionLevel Protectable::getProtectionLevel() const
{
	if (m_level == PROTECTION_DEFAULT)
	{
		return defaultProtectionLevel();
	}
	
	return m_level;
}