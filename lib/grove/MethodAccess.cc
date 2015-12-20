/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/MethodAccess.h>
#include <grove/ClassDecl.h>
#include <grove/ExpressionCall.h>
#include <grove/AccessExpr.h>
#include <grove/Module.h>
#include <grove/ReferenceExpr.h>

#include <grove/types/Type.h>
#include <grove/types/FunctionType.h>

#include <grove/exceptions/code_error.h>

#include <util/assertions.h>

void MethodAccess::findDependencies()
{
	auto&& all_named = m_class->getAllNamed(m_name, nullptr);
	for (auto&& named : all_named)
	{
		addDependency(named->as<ASTNode *>());
	}
}

void MethodAccess::resolve()
{
	// The first thing to do is verify that we're being used in the
	// context of a function call.
	auto call = findParent<ExpressionCall *>();
	if (call == nullptr)
	{
		throw code_error(this, [] () { return "Accessing a method must be used "
			"in the context of a method call."; });
	}
	
	// Now, we want to get the "this" parameter from the nearest AccessExpr.
	auto access = findParent<AccessExpr *>();
	if (access == nullptr)
	{
		throw code_error(this, [] () { return "Method call not being used in "
			"the context of an object access."; });
	}
	
	Expression* this_arg = new NodeReference(access->getLHS());
	getModule()->findDependencies(this_arg);
	getModule()->resolve(this_arg);
	
	if (this_arg->getType()->isPointerTy() == false)
	{
		this_arg = new ReferenceExpr(this_arg);
		getModule()->findDependencies(this_arg);
		getModule()->resolve(this_arg);
	}
	
	call->addArgument(this_arg, 0);
	
	SearchSettings settings;
	settings.createGeneric = true;
	settings.forceTypeMatch = false;
	settings.includeLimit = false;
	settings.searchWholeTree = false;
	
	auto named = m_class->getNamed(m_name, call->expectedFunctionTy(), nullptr, settings);
	setNode(named->as<ASTNode *>());
	
	NodeReference::resolve();
}

MethodAccess::MethodAccess(const ClassDecl* theClass, OString name)
{
	assertExists(theClass, "MethodAccess ctor: m_class is nullptr");
	
	if (name == "")
	{
		throw fatal_error("Creating a method access with an empty name");
	}
	
	m_class = theClass;
	m_name = name;
}