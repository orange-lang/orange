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

std::vector<ASTNode *> ASTNode::getChildren() const
{
	return m_children;
}

void ASTNode::addChild(ASTNode *child)
{
	if (child == nullptr)
	{
		throw std::invalid_argument("child must not be nullptr");
	}
	
	m_children.push_back(child);
}

ASTNode* ASTNode::copy() const
{
	return new ASTNode(getModule());
}

void ASTNode::resolve()
{
	// Do nothing
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
	
	getParent()->addChild(this);
}

ASTNode::~ASTNode()
{
	// Do nothing 
}