/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/Parameter.h>

#include <grove/exceptions/fatal_error.h>

#include <util/assertions.h>

#include <llvm/IR/IRBuilder.h>

llvm::Value* Parameter::getPointer() const
{
	return m_value;
}

bool Parameter::hasPointer() const
{
	return true;
}

llvm::Value* Parameter::getValue() const
{
	return IRBuilder()->CreateLoad(m_value);
}

ASTNode* Parameter::copy() const
{
	return new Parameter(m_type, getName());
}

Parameter::Parameter(Type* type, OString name)
{
	assertExists(type, "Type must not be null");
	
	if (name == "")
	{
		throw fatal_error("name was null");
	}
	
	setType(type);
	m_name = name;
}