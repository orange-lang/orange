/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once 

#include "ObjectBase.h"

class ASTNode;

/**
 * Staticable defines a node that can be declared as static.
 */
class Staticable : virtual public ObjectBase
{
protected:
	bool m_static = false;
public:
	void setStatic(bool isStatic);
	
	const bool getStatic() const;
};