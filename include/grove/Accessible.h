/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

#include "ObjectBase.h"

class Expression;
class Type;

/**
 * Accessible defines classes that can have their members accessed.
 */
class Accessible : public ObjectBase
{
public:
	virtual bool isAccessible() const;
	
	virtual Expression* access(std::string name, Type* hint) const;
};