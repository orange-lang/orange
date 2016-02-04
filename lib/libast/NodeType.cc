/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <libast/types/NodeType.h>

bool NodeType::isNodeTy() const
{
	return true;
}

bool NodeType::canInitializeVar() const
{
	return false;
}

Expression* NodeType::initializeVar() const
{
	return nullptr;
}

NodeType::NodeType(bool isConst)
: Type(isConst)
{
	
}