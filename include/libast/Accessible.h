/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

#include "ObjectBase.h"
#include "OString.h"

class Expression;
class ASTNode;

namespace Orange { class Type; }

/**
 * Accessible defines classes that can have their members accessed.
 */
class Accessible : virtual public ObjectBase
{
public:
	virtual bool isAccessible() const;
	
	/**
	 * Returns an expression that is representative of a value 
	 * from an access of a member by a given name. The expression 
	 * is a new node and must be resolved and built.
	 */
	virtual Expression* access(OString name, const ASTNode* hint) const;
};