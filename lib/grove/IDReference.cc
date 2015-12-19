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
#include <grove/Function.h>
#include <grove/MemberVarDecl.h>
#include <grove/MemberAccess.h>
#include <grove/ClassDecl.h>
#include <grove/ClassMethod.h>
#include <grove/Module.h>

#include <grove/exceptions/undefined_error.h>
#include <grove/exceptions/fatal_error.h>

#include <util/assertions.h>

llvm::Value* IDReference::getPointer() const
{
	return findNode()->getPointer();
}

bool IDReference::hasPointer() const
{
	return findNode()->hasPointer();
}

bool IDReference::transferrable() const
{
	return findNode()->transferrable();
}

Valued* IDReference::findNode() const
{
	return m_node;
}

OString IDReference::getName() const
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

Expression* IDReference::access(OString name, const ASTNode* hint) const
{
	if (isAccessible() == false)
	{
		return nullptr;
	}
	
	return findNode()->as<Accessible *>()->access(name, hint);
}


void IDReference::findDependencies()
{
	auto ref = findNamed(getName(), nullptr);
	
	if (ref == nullptr)
	{
		throw undefined_error(&m_name, m_name);
	} else if (ref->is<MemberVarDecl *>() &&
			   findParent<ClassMethod *>() != nullptr)
	{
		auto access = new MemberAccess(getName());
		addChild(access);
		
		getModule()->findDependencies(access);
		
		m_node = access;
		//throw fatal_error("Can't handle member accesses yet");
	}
	else if (ref->as<ASTNode *>()->findParent<Function *>() !=
			 findParent<Function *>())
	{
		throw undefined_error(&m_name, m_name);
	}
	else
	{
    	m_node = ref->as<Valued *>();
	}
	
	addDependency(m_node->as<ASTNode *>());
}


void IDReference::resolve()
{
	auto typed = m_node->as<Typed *>();
	auto ty = typed->getType();
	assertExists(ty, "Could not assign type.");

	setType(ty);
}

void IDReference::build()
{
	for (auto& child : getChildren())
	{
		child->build();
	}
}

llvm::Value* IDReference::getValue() const
{
	return findNode()->getValue();
}

llvm::Value* IDReference::getSize() const
{
	return findNode()->getSize();
}

IDReference::IDReference(OString name)
{
	if (name == "")
	{
		throw fatal_error("name for id reference was null");
	}

	m_name = name;
}
