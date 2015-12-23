/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/NodeReference.h>
#include <grove/Valued.h>
#include <grove/Named.h>
#include <grove/Typed.h>
#include <grove/Function.h>
#include <grove/MemberVarDecl.h>
#include <grove/MemberAccess.h>
#include <grove/ClassDecl.h>
#include <grove/ClassMethod.h>
#include <grove/Module.h>

#include <grove/exceptions/undefined_error.h>
#include <grove/exceptions/fatal_error.h>

#include <util/assertions.h>

const Valued* NodeReference::nodeAsValued() const
{
	return m_node->as<const Valued *>();
}

llvm::Value* NodeReference::getPointer() const
{
	return nodeAsValued()->getPointer();
}

bool NodeReference::hasPointer() const
{
	return nodeAsValued()->hasPointer();
}

bool NodeReference::transferrable() const
{
	return nodeAsValued()->transferrable();
}

ASTNode* NodeReference::copy() const
{
	return new NodeReference(*this);
}

bool NodeReference::isAccessible() const
{
	return m_node->is<Accessible *>() &&
	m_node->as<Accessible *>()->isAccessible();
}

Expression* NodeReference::access(OString name, const ASTNode* hint) const
{
	if (isAccessible() == false)
	{
		return nullptr;
	}
	
	return m_node->as<Accessible *>()->access(name, hint);
}

void NodeReference::findDependencies()
{
	addDependency(m_node);
}

void NodeReference::resolve()
{
	auto typed = m_node->as<Typed *>();
	auto ty = typed->getType();
	assertExists(ty, "Could not assign type.");
	
	setType(ty);
}

void NodeReference::build()
{
	for (auto& child : getChildren())
	{
		child->build();
	}
}

llvm::Value* NodeReference::getValue() const
{
	return nodeAsValued()->getValue();
}

llvm::Value* NodeReference::getSize() const
{
	return nodeAsValued()->getSize();
}

const ASTNode* NodeReference::getNode() const
{
	return m_node;
}

void NodeReference::setNode(ASTNode *node)
{
	assertExists(node, "node must not be nullptr");
	
	if (node->is<Valued *>() == false)
	{
		throw code_error(node, []() { return "referencing node without a "
			"value!"; });
	}
	
	m_node = node;
}

NodeReference::NodeReference()
{
	// Do nothing.
}

NodeReference::NodeReference(ASTNode* node)
{
	assertExists(node, "NodeReference::NodeReference: node is nullptr");
	
	if (node->is<Valued *>() == false)
	{
		throw code_error(node, []() { return "referencing node without a "
			"value!"; });
	}
	
	m_node = node;
}

NodeReference::NodeReference(const NodeReference& other)
{
	if (getModule()->hasCopy(other.m_node))
	{
		m_node = getModule()->getCopy(other.m_node);
	}
	else
	{
		m_node = other.m_node->copy();
	}
	
	other.defineCopy(this);
}
