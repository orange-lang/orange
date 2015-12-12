/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once 

#include "VarDecl.h"
#include "ClassTopLevel.h"

/**
 * Represents a class member variable declaration.
 */	
class MemberVarDecl : public VarDecl, public ClassTopLevel
{
public:
	/// Gets the offset of this member in the list of members of the class.
	unsigned int getOffset() const;
	
	MemberVarDecl(Type* type, OString name, Expression* expression);
};