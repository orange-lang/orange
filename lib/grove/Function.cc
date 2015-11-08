/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/Function.h>

std::string Function::getName() const
{
	return m_name;
}

Function::Function(ASTNode* parent, std::string name)
: Block(parent)
{
	if (name == "")
	{
		throw std::invalid_argument("name must not be blank.");
	}
	
	m_name = name;
}

Function::Function(Module* module, std::string name)
: Block(module)
{
	if (name == "")
	{
		throw std::invalid_argument("name must not be blank.");
	}
	
	m_name = name;
}