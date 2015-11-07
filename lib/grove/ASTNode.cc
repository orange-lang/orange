/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <stdexcept>
#include <grove/ASTNode.h>

Module* ASTNode::getModule() const
{
	return m_module;
}

ASTNode* ASTNode::getParent() const
{
	return m_parent;
}

ASTNode* ASTNode::copy() const
{
	return new ASTNode(getModule());
}

ASTNode::ASTNode(Module* module)
{
	if (module == nullptr)
	{
		throw std::invalid_argument("module cannot be null.");
	}
	
	m_module = module;
}

ASTNode::ASTNode(ASTNode* parent)
{
	if (parent == nullptr)
	{
		throw std::invalid_argument("parent cannot be null.");
	}
	
	m_parent = parent;
	m_module = getParent()->getModule();
}