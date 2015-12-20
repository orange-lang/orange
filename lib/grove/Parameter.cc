/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/Parameter.h>

#include <grove/exceptions/fatal_error.h>

#include <grove/types/NodeType.h>
#include <grove/types/ReferenceType.h>

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
	auto clone = new Parameter(m_type->copyType(), getName());
	
	defineCopy(clone);
	return clone;
}

bool Parameter::isAccessible() const
{
	// We can have members accessed if we're a reference type,
	// and our reference type is also accessible.
	if (getType()->getRootTy()->is<ReferenceType *>() == false)
	{
		return false;
	}
	
	auto ref = getType()->getRootTy()->as<ReferenceType *>()->getReference();
	return ref->is<Accessible *>() && ref->as<Accessible *>()->isAccessible();
}

Expression* Parameter::access(OString name, const ASTNode *hint) const
{
	if (isAccessible() == false)
	{
		return nullptr;
	}
	
	const ASTNode* hint_to_use = hint;
	if (hint_to_use == nullptr)
	{
		hint_to_use = this;
	}
	
	auto ref = getType()->getRootTy()->as<ReferenceType *>()->getReference();
	auto accessible_ref = ref->as<Accessible *>();
	return accessible_ref->access(name, hint_to_use);
}

Parameter::Parameter(const Type* type, OString name)
{
	assertExists(type, "Type must not be null");
	
	if (name == "")
	{
		throw fatal_error("name was null");
	}
	
	if (type->getRootTy()->is<NodeType *>())
	{
		addChild(type->getRootTy()->as<NodeType *>());
	}
	
	setType(type);
	m_name = name;
}