/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/StaticMethodAccess.h>
#include <grove/ClassDecl.h>
#include <grove/ExpressionCall.h>
#include <grove/AccessExpr.h>
#include <grove/Module.h>
#include <grove/ReferenceExpr.h>

#include <grove/types/Type.h>
#include <grove/types/FunctionType.h>

#include <grove/exceptions/code_error.h>

#include <util/assertions.h>

void StaticMethodAccess::findDependencies()
{
	auto&& all_named = m_class->getAllNamed(m_name, this);
	for (auto&& named : all_named)
	{
		addDependency(named->as<ASTNode *>());
	}
}

ASTNode* StaticMethodAccess::copy() const
{
	return new StaticMethodAccess(*this);
}

std::vector<ObjectBase**> StaticMethodAccess::getMemberNodes()
{
	auto list = NodeReference::getMemberNodes();
	list.insert(list.end(), {
		(ObjectBase **)&m_class
	});
	return list;
}

std::vector<std::vector<ObjectBase *>*> StaticMethodAccess::getMemberLists()
{
	return defMemberLists();
}

void StaticMethodAccess::resolve()
{
	// If we're not referring to a static method, we have to be used
	// in the context of a ReferenceExpr.
	// Otherwise, we can be used in a ReferenceExpr OR ExpressionCall.
	
	// The first thing to do is verify that we're being used in the
	// context of a function call.
	auto ref = findParent<ReferenceExpr *>();
	if (ref == nullptr)
	{
		throw code_error(this, [] () { return "Accessing a non-static method "
			" must be used in the context of a reference."; });
	}
	
	// Now, we want to get the "this" parameter from the nearest AccessExpr.
	auto access = findParent<AccessExpr *>();
	if (access == nullptr)
	{
		throw code_error(this, [] () { return "Method call not being used in "
			"the context of an object access."; });
	}
	
	/// @todo: set to non nullptr when referencing a static class method
	/// via an ExpressionCall.
	FunctionType* expectedTy = nullptr;
	
	SearchSettings settings;
	settings.createGeneric = true;
	settings.forceTypeMatch = false;
	settings.includeLimit = false;
	settings.searchWholeTree = false;
	
	auto named = m_class->getNamed(m_name, expectedTy, this, settings);
	setNode(named->as<ASTNode *>());
	
	if (getNode()->is<Valued *>() == false)
	{
		throw fatal_error("Class method is not valued");
	}
	
	NodeReference::resolve();
}

void StaticMethodAccess::build()
{
	NodeReference::build();
	
	setValue(getNode()->as<Valued *>()->getValue());
}

StaticMethodAccess::StaticMethodAccess(const ClassDecl* theClass, OString name)
{
	assertExists(theClass, "MethodAccess ctor: m_class is nullptr");
	
	if (name == "")
	{
		throw fatal_error("Creating a method access with an empty name");
	}
	
	m_class = theClass;
	m_name = name;
}

StaticMethodAccess::StaticMethodAccess(const StaticMethodAccess& other)
{
	m_class = other.m_class;
	m_name = other.m_name;
	other.defineCopy(this);
}
