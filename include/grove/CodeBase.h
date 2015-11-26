/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once 

#include "ObjectBase.h"
#include "CodeLocation.h"

/**
 * CodeBase is the base class for any code element. It contains references to 
 * location of an element in a file.
 */
class CodeBase : public ObjectBase
{
protected:
	CodeLocation m_location;
public:
	CodeLocation getLocation() const;
	void setLocation(CodeLocation loc);
};