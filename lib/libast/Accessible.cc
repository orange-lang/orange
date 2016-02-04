/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <libast/Accessible.h>

bool Accessible::isAccessible() const
{
	return false;
}

Expression* Accessible::access(OString name, const ASTNode* hint) const
{
	// Do nothing by default.
	return nullptr;
}