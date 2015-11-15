/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/Parameter.h>
#include <util/assertions.h>

#include <llvm/IR/IRBuilder.h>

llvm::Value* Parameter::getValue() const
{
	return IRBuilder()->CreateLoad(m_value);
}

Parameter::Parameter(Type* type, std::string name)
{
	assertExists(type, "Type must not be null");
	
	if (name == "")
	{
		throw std::invalid_argument("name must not be empty");
	}
	
	setType(type);
	m_name = name;
}