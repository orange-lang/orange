/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/IDReference.h>
#include <grove/Valued.h>
#include <grove/Named.h>
#include <grove/Typed.h>

#include <util/assertions.h>

llvm::Value* IDReference::getPointer() const
{
	return findNode()->getPointer();
}

bool IDReference::hasPointer() const
{
	return findNode()->hasPointer();
}

Valued* IDReference::findNode() const
{
	return m_node;
}

std::string IDReference::getName() const
{
	return m_name;
}

ASTNode* IDReference::copy() const
{
	return new IDReference(m_name);
}


bool IDReference::isAccessible() const
{
	return findNode()->is<Accessible *>() &&
		findNode()->as<Accessible *>()->isAccessible();
}

Expression* IDReference::access(std::string name, Type* hint) const
{
	if (isAccessible() == false)
	{
		return nullptr;
	}
	
	return findNode()->as<Accessible *>()->access(name, hint);
}


void IDReference::findDependencies()
{
	auto ref = findNamed(getName());
	assertExists(ref, "No variable with this name exists.");
	
	addDependency(ref->as<ASTNode *>());
}


void IDReference::resolve()
{
	m_node = findNamed(getName())->as<Valued *>();
	
	assertExists(m_node, "No variable with this name exists.");

	auto typed = m_node->as<Typed *>();
	auto ty = typed->getType();
	assertExists(ty, "Could not assign type.");

	setType(ty);
}

llvm::Value* IDReference::getValue() const
{
	return findNode()->getValue();
}

IDReference::IDReference(std::string name)
{
	if (name == "")
	{
		throw std::invalid_argument("name cannot be null.");
	}

	m_name = name;
}
